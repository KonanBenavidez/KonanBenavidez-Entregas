// Copyright Epic Games, Inc. All Rights Reserved.

#include "pruebaGameMode.h"
#include "pruebaCharacter.h"
#include "UObject/ConstructorHelpers.h"

ApruebaGameMode::ApruebaGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
