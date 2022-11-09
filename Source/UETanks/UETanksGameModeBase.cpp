// Copyright Epic Games, Inc. All Rights Reserved.


#include "UETanksGameModeBase.h"

#include "BaseTank.h"

AUETanksGameModeBase::AUETanksGameModeBase()
{
	DefaultPawnClass = DefaultPawn->StaticClass();
}
