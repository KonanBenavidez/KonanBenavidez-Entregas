// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PEV2_PlayerController.generated.h"

UCLASS()
class PRUEBA_API APEV2_PlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    UFUNCTION(Client, Reliable)
    void Client_ShowHitFeedback();

    UFUNCTION(Client, Reliable)
    void Client_ShowDeathScreen(const FString& GanadorNombre);

    UFUNCTION(Client, Reliable)
    void Client_UpdateHUD(float Vida, float VidaMax);

    UFUNCTION(BlueprintImplementableEvent)
    void BP_OnHitFeedback();

    UFUNCTION(BlueprintImplementableEvent)
    void BP_OnDeathScreen(const FString& GanadorNombre);

    UFUNCTION(BlueprintImplementableEvent)
    void BP_OnUpdateHUD(float Vida, float VidaMax);
};