// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

AMyCharacter::AMyCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    ScannerComponent = CreateDefaultSubobject<UScannerComponent>(TEXT("ScannerComponent"));
}

void AMyCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void AMyCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAction("Scan", IE_Pressed, this, &AMyCharacter::StartScan);
    PlayerInputComponent->BindAction("Scan", IE_Released, this, &AMyCharacter::StopScan);
}

void AMyCharacter::StartScan()
{
    ScannerComponent->StartScan();
    {
        UE_LOG(LogTemp, Warning, TEXT("StartScan llamado"));
        ScannerComponent->StartScan();
    }
}

void AMyCharacter::StopScan()
{
    ScannerComponent->StopScan();
}
