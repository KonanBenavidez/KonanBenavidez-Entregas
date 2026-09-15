// Copyright Epic Games, Inc. All Rights Reserved.

#include "pruebaCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Net/UnrealNetwork.h"
#include "pruebaGameMode.h"
#include "PEV2_PlayerController.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ApruebaCharacter::ApruebaCharacter()
{
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
    GetCharacterMovement()->JumpZVelocity = 700.f;
    GetCharacterMovement()->AirControl = 0.35f;
    GetCharacterMovement()->MaxWalkSpeed = 500.f;
    GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
    GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
    GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 400.0f;
    CameraBoom->bUsePawnControlRotation = true;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    FollowCamera->bUsePawnControlRotation = false;

    bReplicates = true;
}

void ApruebaCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void ApruebaCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(ApruebaCharacter, Vida);
    DOREPLIFETIME(ApruebaCharacter, bMuerto);
}

void ApruebaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }
    }

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ApruebaCharacter::Move);
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ApruebaCharacter::Look);
        EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &ApruebaCharacter::Disparar);
    }
}

void ApruebaCharacter::Move(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>();
    if (Controller != nullptr)
    {
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);
        const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        AddMovementInput(ForwardDirection, MovementVector.Y);
        AddMovementInput(RightDirection, MovementVector.X);
    }
}

void ApruebaCharacter::Look(const FInputActionValue& Value)
{
    FVector2D LookAxisVector = Value.Get<FVector2D>();
    if (Controller != nullptr)
    {
        AddControllerYawInput(LookAxisVector.X);
        AddControllerPitchInput(LookAxisVector.Y);
    }
}

void ApruebaCharacter::Disparar()
{
    if (bMuerto) return;
    FVector Origen = FollowCamera->GetComponentLocation();
    FVector Direccion = FollowCamera->GetForwardVector();
    Server_Disparar(Origen, Direccion);
}

bool ApruebaCharacter::Server_Disparar_Validate(FVector Origen, FVector Direccion)
{
    return true;
}

void ApruebaCharacter::Server_Disparar_Implementation(FVector Origen, FVector Direccion)
{
    if (!ProyectilClass || bMuerto) return;

    FActorSpawnParameters Params;
    Params.Owner = this;
    Params.Instigator = this;
    Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    FRotator SpawnRotation = Direccion.Rotation();
    GetWorld()->SpawnActor<AActor>(ProyectilClass, Origen, SpawnRotation, Params);
}

void ApruebaCharacter::RecibirDanio(float Danio, AController* InstigadorController)
{
    if (!HasAuthority() || bMuerto) return;

    Vida -= Danio;
    Vida = FMath::Clamp(Vida, 0.f, VidaMax);

    APEV2_PlayerController* PC = Cast<APEV2_PlayerController>(GetController());
    if (PC) PC->Client_UpdateHUD(Vida, VidaMax);

    if (Vida <= 0.f)
    {
        bMuerto = true;
        Multicast_PlayDeathEffect();

        if (InstigadorController)
        {
            ApruebaGameMode* GM = GetWorld()->GetAuthGameMode<ApruebaGameMode>();
            if (GM)
            {
                APlayerController* InstigadorPC = Cast<APlayerController>(InstigadorController);
                APlayerController* VictimaPC = Cast<APlayerController>(GetController());
                GM->NotificarKill(InstigadorPC, VictimaPC);
            }
        }
    }
}

void ApruebaCharacter::OnRep_Vida()
{
    BP_OnVidaCambia(Vida, VidaMax);
}

void ApruebaCharacter::OnRep_bMuerto()
{
    if (bMuerto) BP_OnMuerto();
}

void ApruebaCharacter::Multicast_PlayDeathEffect_Implementation()
{
    BP_OnMuerto();
}