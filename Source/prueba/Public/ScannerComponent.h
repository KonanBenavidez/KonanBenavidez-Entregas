// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ScanData.h"
#include "ScannerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScanProgress, float, Progreso);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScanComplete, FScanData, DatosEscaneados);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnScanCancelled);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PRUEBA_API UScannerComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UScannerComponent();

    virtual void TickComponent(float DeltaTime, ELevelTick TickType,
        FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable)
    void StartScan();

    UFUNCTION(BlueprintCallable)
    void StopScan();

    UPROPERTY(BlueprintReadOnly)
    TArray<FScanData> Codice;

    UPROPERTY(BlueprintAssignable)
    FOnScanProgress OnScanProgress;

    UPROPERTY(BlueprintAssignable)
    FOnScanComplete OnScanComplete;

    UPROPERTY(BlueprintAssignable)
    FOnScanCancelled OnScanCancelled;

    UPROPERTY(EditAnywhere)
    float ScanRange = 1000.f;

private:
    bool bIsScanning = false;
    float ScanProgress = 0.f;
    FScanData CurrentScanData;
    AActor* CurrentTarget = nullptr;

    AActor* GetScannableActorInView();
    bool IsAlreadyScanned(const FScanData& Data);
};