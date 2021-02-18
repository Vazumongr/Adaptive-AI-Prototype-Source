// Copyright Epic Games, Inc. All Rights Reserved.

#include "StrongerTogetherGameMode.h"
#include "StrongerTogetherCharacter.h"
#include "UObject/ConstructorHelpers.h"

AStrongerTogetherGameMode::AStrongerTogetherGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
