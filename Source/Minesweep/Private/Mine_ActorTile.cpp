// Fill out your copyright notice in the Description page of Project Settings.

#include "Mine_ActorTile.h"
#include "MinesweepGameModeBase.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AMine_ActorTile::AMine_ActorTile()
{
	// remove tick
	PrimaryActorTick.bCanEverTick = false;
	isFlagged = false;
}

// BeginPlay override
void AMine_ActorTile::BeginPlay()
{
	Super::BeginPlay();
}

// Called when tile is clicked by player
void AMine_ActorTile::ClickTile()
{
	// check if the tile is already clicked, or has been flagged as a mine
	if (!isClicked && !isFlagged)
	{
		// set to clicked, retrieve the grid to set tile to revealed
		isClicked = true;
		AMinesweepGameModeBase* GameMode = Cast<AMinesweepGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		GameMode->GetGrid()->RevealTile(xLoc, yLoc);
	}
}

// Flag or Unflag tile
void AMine_ActorTile::ChangeFlag()
{
	// only change if not already clicked
	if (!isClicked)
	{
		// set to flag, FlagTile is set in blueprint (sets visuals)
		isFlagged = !isFlagged;
		FlagTile(isFlagged);
	}
}

// Move actor to location
void AMine_ActorTile::SetPos(int x, int y)
{
	xLoc = x;
	yLoc = y;
}
