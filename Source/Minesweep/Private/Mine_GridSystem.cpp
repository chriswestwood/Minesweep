// Fill out your copyright notice in the Description page of Project Settings.


#include "Mine_GridSystem.h"

// Sets default values
AMine_GridSystem::AMine_GridSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMine_GridSystem::BeginPlay()
{
	Super::BeginPlay();

	// TODO: get grdwidth and gridheight from settings
	CreateGrid();

	//TEST
	CreateMines(4, 4);
	RevealTile(4, 4);
	//RevealAll();
}

// Called every frame
void AMine_GridSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMine_GridSystem::CreateGrid()
{
	// TODO: init array
	FActorSpawnParameters spawnParam;
	for (int width = 0; width < gridWidth; width++)
	{
		tileArray.AddDefaulted();
		for (int height = 0; height < gridHeight; height++)
		{
			AMine_ActorTile* tile = GetWorld()->SpawnActor<AMine_ActorTile>(tileBlueprint, 
																			FVector(width * 64, 0, height*64), 
																			FRotator(0, 0, 0), 
																			spawnParam);
			tileArray[width].AddDefaulted();
			tileArray[width][height].SetTile(tile);
		}
	}
}

void AMine_GridSystem::CreateMines(int clickX, int clickY)
{
	// create x * y array of ints
	TArray<TArray<int>> bombArray;
	for (int i = 0; i < gridHeight; i++)
	{
		TArray<int> bombValues;
		for (int j = 0; j < gridWidth; j++)
		{
			bombValues.Add(0);
		}
		bombArray.Add(bombValues);
	}
	for (int i = 0; i < mineCount; i++)
	{
		int xLoc = FMath::RandRange(0, gridWidth-1);
		int yLoc = FMath::RandRange(0, gridHeight-1);
		if (xLoc == clickX && yLoc == clickY || bombArray[xLoc][yLoc] > 8)	{i--; continue;}
		bombArray[xLoc][yLoc] = 10; // set to 10 as any tile weights are not going to exceed 8
		//increase surrounding tiles weight
		if (xLoc > 0)
		{
			bombArray[xLoc - 1][yLoc]++;
			if (yLoc > 0) { bombArray[xLoc - 1][yLoc - 1]++; }
			if (yLoc < gridHeight-1){bombArray[xLoc - 1][yLoc + 1]++;}
		}
		if (xLoc < gridWidth - 1)
		{
			bombArray[xLoc + 1][yLoc]++;
			if (yLoc > 0) { bombArray[xLoc + 1][yLoc - 1]++; }
			if (yLoc < gridHeight-1) { bombArray[xLoc + 1][yLoc + 1]++; }
		}
		if (yLoc > 0){bombArray[xLoc][yLoc - 1]++;}
		if (yLoc < gridHeight-1){bombArray[xLoc][yLoc + 1]++;}
	}
	for (int y = 0; y < gridHeight; y++)
	{
		for (int x = 0; x < gridWidth; x++)
		{
			tileArray[y][x].SetMine(bombArray[y][x]);
		}
	}
}

void AMine_GridSystem::RevealTile(int x, int y)
{
	if (x > gridWidth-1 || x <0 || y > gridHeight-1 || y <0 ) // x or y out of bounds
		return;

	if (!tileArray[x][y].isRevealed)
	{
		tileArray[x][y].SetRevealed();
		tileArray[x][y].tile->ShowTile(tileArray[x][y].isMine,tileArray[x][y].mineWeight);
		if (tileArray[x][y].isBlank()) { RevealAdjacent(x, y); }
	}
}

void AMine_GridSystem::RevealAll()
{
	for (int y = 0; y < gridHeight; y++)
	{
		for (int x = 0; x < gridWidth; x++)
		{
			RevealTile(x, y);
		}
	}
}

void AMine_GridSystem::RevealAdjacent(int x, int y)
{
	if (x > 0)
	{		
		RevealTile(x - 1, y);
		if (y > 0) { RevealTile(x - 1, y - 1);}
		if (y< gridHeight-1) { RevealTile(x - 1, y + 1);}
	}
	if (x < gridWidth-1)
	{
		RevealTile(x + 1, y);
		if (y> 0) { RevealTile(x + 1, y - 1); }
		if (y < gridHeight-1) { RevealTile(x + 1, y + 1); }
	}
	if (y > 0) {RevealTile(x, y - 1);}
	if (y < gridHeight-1) { RevealTile(x, y + 1); }
}

