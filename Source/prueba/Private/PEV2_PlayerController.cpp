// Fill out your copyright notice in the Description page of Project Settings.


#include "PEV2_PlayerController.h"

void APEV2_PlayerController::Client_ShowHitFeedback_Implementation()
{
    BP_OnHitFeedback();
}

void APEV2_PlayerController::Client_ShowDeathScreen_Implementation(const FString& GanadorNombre)
{
    BP_OnDeathScreen(GanadorNombre);
}

void APEV2_PlayerController::Client_UpdateHUD_Implementation(float Vida, float VidaMax)
{
    BP_OnUpdateHUD(Vida, VidaMax);
}
