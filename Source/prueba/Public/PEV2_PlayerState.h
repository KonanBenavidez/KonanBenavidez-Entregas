// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PEV2_PlayerState.generated.h"

UCLASS()
class PRUEBA_API APEV2_PlayerState : public APlayerState
{
    GENERATED_BODY()

public:
    UPROPERTY(ReplicatedUsing = OnRep_Kills, BlueprintReadOnly)
    int32 Kills = 0;

    UPROPERTY(Replicated, BlueprintReadOnly)
    int32 Muertes = 0;

    UFUNCTION()
    void OnRep_Kills();

    UFUNCTION(BlueprintCallable)
    void AgregarKill();

    UFUNCTION(BlueprintCallable)
    void AgregarMuerte();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};