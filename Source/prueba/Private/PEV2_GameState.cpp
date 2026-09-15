// Fill out your copyright notice in the Description page of Project Settings.


#include "PEV2_GameState.h"
#include "Net/UnrealNetwork.h"

void APEV2_GameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(APEV2_GameState, TiempoRestante);
    DOREPLIFETIME(APEV2_GameState, EstadoPartida);
    DOREPLIFETIME(APEV2_GameState, GanadorNombre);
}

void APEV2_GameState::OnRep_TiempoRestante()
{
    
}

void APEV2_GameState::OnRep_EstadoPartida()
{
    
}