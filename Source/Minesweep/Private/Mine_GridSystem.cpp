// Fill out your copyright notice in the Description page of Project Settings.


#include "Mine_GridSystem.h"
#include "MinesweepGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMine_GridSystem::AMine_GridSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AMine_GridSystem::BeginPlay()
{
	Super::BeginPlay();

	// TODO: get grdwidth and gridheight from settings
	CreateGrid();
	hasGeneratedMines = false;
}

// Called every frame
void AMine_GridSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMine_GridSystem::CreateGrid()
{
	if (tileBlueprint == nullptr) return;
	for (int width = 0; width < gridWidth; width++)
	{
		tileArray.AddDefaulted();
		for (int height = 0; height < gridHeight; height++)
		{
			AMine_ActorTile* tile = GetWorld()->SpawnActor<AMine_ActorTile>(tileBlueprint, 
																			FVector(width * 64, 0, height*64), 
																			FRotator(0, 0, 0));
			tile->SetPos(width, height);
			tileArray[width].AddDefaulted();
			tileArray[width][height].SetTile(tile);
		}
	}
	gridScore = 0;
}

void AMine_GridSystem::CreateMines(int clickX, int clickY)
{
	hasGeneratedMines = true;
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
	if (x > gridWidth - 1 || x <0 || y > gridHeight - 1 || y < 0) // x or y out of bounds
		return;
	if (!hasGeneratedMines)	CreateMines(x, y);
	if (!tileArray[x][y].isRevealed)
	{
		tileArray[x][y].SetRevealed();
		tileArray[x][y].tile->ShowTile(tileArray[x][y].isMine,tileArray[x][y].mineWeight);
		if (tileArray[x][y].IsBlank())  RevealAdjacent(x, y); 
		if (tileArray[x][y].IsMine()) 
		{ 
			RevealAll(); 
			AMinesweepGameModeBase* gameMode = Cast<AMinesweepGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
			gameMode->EndGame(false, gridScore);
		}
		gridScore++;
		//Check for win conditions
		CheckWin();
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

void AMine_GridSystem::CheckWin()
{
	for (int y = 0; y < gridHeight; y++)
	{
		for (int x = 0; x < gridWidth; x++)
		{
			if (!tileArray[y][x].isRevealed && !tileArray[y][x].IsMine()) return;
		}
	}
	// All non-mine tiles have been revealed, set level win
	AMinesweepGameModeBase* gameMode = Cast<AMinesweepGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	gameMode->EndGame(true, gridScore);


}

