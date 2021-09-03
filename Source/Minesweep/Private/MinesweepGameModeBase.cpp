// Copyright Epic Games, Inc. All Rights Reserved.


#include "MinesweepGameModeBase.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

AMinesweepGameModeBase::AMinesweepGameModeBase()
{
	DefaultPawnClass = AMine_PlayerPawn::StaticClass();
	PlayerControllerClass = AMine_PlayerController::StaticClass();
	AMine_GridSystem* foundGrid = Cast<AMine_GridSystem>(UGameplayStatics::GetActorOfClass(GetWorld(), AMine_GridSystem::StaticClass()));
	SetGrid(foundGrid);
}

AMine_GridSystem* AMinesweepGameModeBase::GetGrid()
{
	return gridSystem;
}

void AMinesweepGameModeBase::SetGrid(AMine_GridSystem* g)
{
	if (g != nullptr) gridSystem = g;
}

void AMinesweepGameModeBase::EndGame(bool isWin, int score)
{
	// disable player input
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	PC->DisableInput(NULL);

	// show game over screen w/ stats
}
