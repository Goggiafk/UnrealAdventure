// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealAdventureGameMode.h"
#include "UnrealAdventureCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUnrealAdventureGameMode::AUnrealAdventureGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
