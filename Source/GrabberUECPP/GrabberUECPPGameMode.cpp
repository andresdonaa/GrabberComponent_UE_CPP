// Copyright Epic Games, Inc. All Rights Reserved.

#include "GrabberUECPPGameMode.h"
#include "GrabberUECPPCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGrabberUECPPGameMode::AGrabberUECPPGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
