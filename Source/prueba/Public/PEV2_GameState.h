// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "PEV2_GameState.generated.h"

UENUM(BlueprintType)
enum class EEstadoPartida : uint8
{
    Lobby,
    Jugando,
    Fin
};

UCLASS()
class PRUEBA_API APEV2_GameState : public AGameState
{
    GENERATED_BODY()

public:
    UPROPERTY(ReplicatedUsing = OnRep_TiempoRestante, BlueprintReadOnly)
    float TiempoRestante = 300.f;

    UPROPERTY(ReplicatedUsing = OnRep_EstadoPartida, BlueprintReadOnly)
    EEstadoPartida EstadoPartida = EEstadoPartida::Lobby;

    UPROPERTY(Replicated, BlueprintReadOnly)
    FString GanadorNombre;

    UFUNCTION()
    void OnRep_TiempoRestante();

    UFUNCTION()
    void OnRep_EstadoPartida();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
}; 
