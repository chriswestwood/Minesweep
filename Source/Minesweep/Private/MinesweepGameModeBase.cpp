// Copyright Epic Games, Inc. All Rights Reserved.


#include "MinesweepGameModeBase.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

// setup defaults
AMinesweepGameModeBase::AMinesweepGameModeBase()
{
	DefaultPawnClass = AMine_PlayerPawn::StaticClass();
	PlayerControllerClass = AMine_PlayerController::StaticClass();
	AMine_GridSystem* foundGrid = Cast<AMine_GridSystem>(UGameplayStatics::GetActorOfClass(GetWorld(), AMine_GridSystem::StaticClass()));
	SetGrid(foundGrid);
}

// retrieve the grid system
AMine_GridSystem* AMinesweepGameModeBase::GetGrid()
{
	return gridSystem;
}

// Set the grid system
void AMinesweepGameModeBase::SetGrid(AMine_GridSystem* g)
{
	if (g != nullptr) gridSystem = g;
}

// End the game
void AMinesweepGameModeBase::EndGame(bool isWin, int score)
{
	// disable player input
	AMine_PlayerController* PC = Cast<AMine_PlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	PC->SetGameEnd(score, isWin);
}
