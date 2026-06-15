#pragma once
#include "CoreMinimal.h"
#include "ScanData.generated.h"

USTRUCT(BlueprintType)
struct FScanData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FString Nombre;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FString Descripcion;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FString Tipo;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float TiempoEscaneo = 2.f;
};