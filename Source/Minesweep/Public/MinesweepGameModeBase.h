// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Mine_PlayerPawn.h"
#include "Mine_PlayerController.h"
#include "Mine_GridSystem.h"
#include "MinesweepGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MINESWEEP_API AMinesweepGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	

public:
	AMinesweepGameModeBase();

	AMine_GridSystem* GetGrid();
	void SetGrid(AMine_GridSystem* g);
	void EndGame(bool isWin, int score);

private:

	AMine_GridSystem* gridSystem;
};
