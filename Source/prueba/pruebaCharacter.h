// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "pruebaCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config = Game)
class ApruebaCharacter : public ACharacter
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    USpringArmComponent* CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
    UCameraComponent* FollowCamera;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputMappingContext* DefaultMappingContext;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* JumpAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* LookAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
    UInputAction* ShootAction;

public:
    ApruebaCharacter();

    // --- Red ---
    UPROPERTY(ReplicatedUsing = OnRep_Vida, BlueprintReadOnly, Category = "Combat")
    float Vida = 100.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
    float VidaMax = 100.f;

    UPROPERTY(ReplicatedUsing = OnRep_bMuerto, BlueprintReadOnly, Category = "Combat")
    bool bMuerto = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    TSubclassOf<AActor> ProyectilClass;

    // --- RepNotify ---
    UFUNCTION()
    void OnRep_Vida();

    UFUNCTION()
    void OnRep_bMuerto();

    // --- Server RPC ---
    UFUNCTION(Server, Reliable, WithValidation)
    void Server_Disparar(FVector Origen, FVector Direccion);

    // --- NetMulticast RPC ---
    UFUNCTION(NetMulticast, Reliable)
    void Multicast_PlayDeathEffect();

    // --- Daño ---
    UFUNCTION(BlueprintCallable)
    void RecibirDanio(float Danio, AController* InstigadorController);

    // --- Blueprint events ---
    UFUNCTION(BlueprintImplementableEvent)
    void BP_OnVidaCambia(float VidaActual, float VidaMaxima);

    UFUNCTION(BlueprintImplementableEvent)
    void BP_OnMuerto();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    void Disparar();

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual void BeginPlay() override;

public:
    FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
    FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

