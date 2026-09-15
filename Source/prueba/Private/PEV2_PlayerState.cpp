// Fill out your copyright notice in the Description page of Project Settings.


#include "PEV2_PlayerState.h"
#include "Net/UnrealNetwork.h"

void APEV2_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(APEV2_PlayerState, Kills);
    DOREPLIFETIME(APEV2_PlayerState, Muertes);
}

void APEV2_PlayerState::OnRep_Kills()
{
    // Blueprint actualiza el scoreboard
}

void APEV2_PlayerState::AgregarKill()
{
    if (GetLocalRole() == ROLE_Authority)
    {
        Kills++;
    }
}

void APEV2_PlayerState::AgregarMuerte()
{
    if (GetLocalRole() == ROLE_Authority)
    {
        Muertes++;
    }
}