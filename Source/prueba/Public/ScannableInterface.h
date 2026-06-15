// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ScanData.h"
#include "ScannableInterface.generated.h"

UINTERFACE(MinimalAPI)
class UScannableInterface : public UInterface
{
    GENERATED_BODY()
};

class PRUEBA_API IScannableInterface
{
    GENERATED_BODY()

public:
    virtual FScanData GetScanData() const = 0;
};