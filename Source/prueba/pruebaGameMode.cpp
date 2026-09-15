// Copyright Epic Games, Inc. All Rights Reserved.

#include "pruebaGameMode.h"
#include "PEV2_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "EngineUtils.h"

ApruebaGameMode::ApruebaGameMode()
{
    PrimaryActorTick.bCanEverTick = true;
    GameStateClass = APEV2_GameState::StaticClass();
    PlayerStateClass = APEV2_PlayerState::StaticClass();
    PlayerControllerClass = APEV2_PlayerController::StaticClass();
}

void ApruebaGameMode::BeginPlay()
{
    Super::BeginPlay();

    APEV2_GameState* GS = GetGameState<APEV2_GameState>();
    if (GS)
    {
        GS->TiempoRestante = TiempoPartida;
        GS->EstadoPartida = EEstadoPartida::Jugando;
    }
}

void ApruebaGameMode::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (!bPartidaTerminada)
    {
        ActualizarTiempo(DeltaTime);
    }
}

void ApruebaGameMode::ActualizarTiempo(float DeltaTime)
{
    APEV2_GameState* GS = GetGameState<APEV2_GameState>();
    if (!GS) return;

    GS->TiempoRestante -= DeltaTime;

    if (GS->TiempoRestante <= 0.f)
    {
        GS->TiempoRestante = 0.f;
        TerminarPartida(nullptr);
    }
}

void ApruebaGameMode::NotificarKill(APlayerController* Asesino, APlayerController* Victima)
{
    if (!Asesino || !Victima) return;

    APEV2_PlayerState* AsesinoPS = Asesino->GetPlayerState<APEV2_PlayerState>();
    APEV2_PlayerState* VictimaPS = Victima->GetPlayerState<APEV2_PlayerState>();

    if (AsesinoPS) AsesinoPS->AgregarKill();
    if (VictimaPS) VictimaPS->AgregarMuerte();

    if (AsesinoPS && AsesinoPS->Kills >= KillsParaGanar)
    {
        TerminarPartida(Asesino);
    }

    RespawnJugador(Victima);
}

void ApruebaGameMode::RespawnJugador(APlayerController* Controller)
{
    if (!Controller) return;

    APawn* PawnViejo = Controller->GetPawn();
    if (PawnViejo) PawnViejo->Destroy();

    TArray<AActor*> PlayerStarts;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);

    if (PlayerStarts.Num() == 0) return;

    AActor* SpawnPoint = PlayerStarts[FMath::RandRange(0, PlayerStarts.Num() - 1)];
    RestartPlayerAtPlayerStart(Controller, SpawnPoint);
}

void ApruebaGameMode::TerminarPartida(APlayerController* Ganador)
{
    bPartidaTerminada = true;

    APEV2_GameState* GS = GetGameState<APEV2_GameState>();
    if (GS)
    {
        GS->EstadoPartida = EEstadoPartida::Fin;
        if (Ganador)
        {
            APEV2_PlayerState* PS = Ganador->GetPlayerState<APEV2_PlayerState>();
            if (PS) GS->GanadorNombre = PS->GetPlayerName();
        }
        else
        {
            GS->GanadorNombre = TEXT("Nadie - Tiempo agotado");
        }
    }

    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        APEV2_PlayerController* PC = Cast<APEV2_PlayerController>(It->Get());
        if (PC && GS)
        {
            PC->Client_ShowDeathScreen(GS->GanadorNombre);
        }
    }
}
