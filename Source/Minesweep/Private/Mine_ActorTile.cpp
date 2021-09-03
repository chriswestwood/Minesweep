// Fill out your copyright notice in the Description page of Project Settings.

#include "Mine_ActorTile.h"
#include "MinesweepGameModeBase.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AMine_ActorTile::AMine_ActorTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMine_ActorTile::BeginPlay()
{
	Super::BeginPlay();
	isFlagged = false;
	
}

// Called every frame
void AMine_ActorTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMine_ActorTile::ClickTile()
{
	if (!isClicked && !isFlagged)
	{
		isClicked = true;
		// TODO: call grid system reveal tile
		AMinesweepGameModeBase* GameMode = Cast<AMinesweepGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
		GameMode->GetGrid()->RevealTile(xLoc, yLoc);
	}
}

void AMine_ActorTile::ChangeFlag()
{
	if (!isClicked)
	{
		isFlagged = !isFlagged;
		FlagTile(isFlagged);
	}
}

void AMine_ActorTile::SetPos(int x, int y)
{
	xLoc = x;
	yLoc = y;
}
