// Fill out your copyright notice in the Description page of Project Settings.


#include "ScannerComponent.h"
#include "ScannableInterface.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"

UScannerComponent::UScannerComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UScannerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!bIsScanning) return;

    AActor* Target = GetScannableActorInView();

    if (!Target || Target != CurrentTarget)
    {
        StopScan();
        return;
    }

    ScanProgress += DeltaTime / CurrentScanData.TiempoEscaneo;
    ScanProgress = FMath::Clamp(ScanProgress, 0.f, 1.f);

    OnScanProgress.Broadcast(ScanProgress);

    if (ScanProgress >= 1.f)
    {
        if (!IsAlreadyScanned(CurrentScanData))
        {
            Codice.Add(CurrentScanData);
        }

        OnScanComplete.Broadcast(CurrentScanData);
        StopScan();
    }
}

void UScannerComponent::StartScan()
{
    AActor* Target = GetScannableActorInView();
    if (!Target) return;

    CurrentTarget = Target;
    CurrentScanData = Cast<IScannableInterface>(Target)->GetScanData();
    bIsScanning = true;
    ScanProgress = 0.f;
}

void UScannerComponent::StopScan()
{
    if (bIsScanning)
    {
        OnScanCancelled.Broadcast();
    }

    bIsScanning = false;
    ScanProgress = 0.f;
    CurrentTarget = nullptr;
}

AActor* UScannerComponent::GetScannableActorInView()
{
    UE_LOG(LogTemp, Warning, TEXT("GetScannableActorInView llamado"));

    AActor* Owner = GetOwner();
    if (!Owner)
    {
        UE_LOG(LogTemp, Warning, TEXT("Owner es null"));
        return nullptr;
    }

    UCameraComponent* Camera = Owner->FindComponentByClass<UCameraComponent>();
    if (!Camera)
    {
        UE_LOG(LogTemp, Warning, TEXT("Camera es null"));
        return nullptr;
    }

    FVector Start = Camera->GetComponentLocation();
    FVector End = Start + Camera->GetForwardVector() * ScanRange;

    FHitResult HitResult;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(Owner);

    DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 0.1f);

    bool bHit = GetWorld()->LineTraceSingleByChannel(
        HitResult, Start, End, ECC_Visibility, Params
    );

    if (bHit && HitResult.GetActor())
    {
        if (HitResult.GetActor()->Implements<UScannableInterface>())
        {
            return HitResult.GetActor();
        }
    }

    return nullptr;
}
    
    bool UScannerComponent::IsAlreadyScanned(const FScanData & Data)
    {
        for (const FScanData& Entry : Codice)
        {
            if (Entry.Nombre == Data.Nombre) return true;
        }
        return false;
    }