// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PEV2_GameState.h"
#include "PEV2_PlayerState.h"
#include "pruebaGameMode.generated.h"

UCLASS()
class PRUEBA_API ApruebaGameMode : public AGameMode
{
    GENERATED_BODY()

public:
    ApruebaGameMode();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 KillsParaGanar = 10;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TiempoPartida = 300.f;

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable)
    void NotificarKill(APlayerController* Asesino, APlayerController* Victima);

    UFUNCTION(BlueprintCallable)
    void RespawnJugador(APlayerController* Controller);

private:
    void TerminarPartida(APlayerController* Ganador);
    void ActualizarTiempo(float DeltaTime);
    bool bPartidaTerminada = false;
};


