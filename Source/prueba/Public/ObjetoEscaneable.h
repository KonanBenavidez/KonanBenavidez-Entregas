// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScannableInterface.h"
#include "ScanData.h"
#include "ObjetoEscaneable.generated.h"

UCLASS()
class PRUEBA_API AObjetoEscaneable : public AActor, public IScannableInterface
{
    GENERATED_BODY()

public:
    AObjetoEscaneable();

    virtual FScanData GetScanData() const override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FScanData DatosEscaneo;
};