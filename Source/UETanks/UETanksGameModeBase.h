// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UETanksGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class UETANKS_API AUETanksGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	AUETanksGameModeBase();

	UPROPERTY(EditAnywhere)
	APawn* DefaultPawn;
};
