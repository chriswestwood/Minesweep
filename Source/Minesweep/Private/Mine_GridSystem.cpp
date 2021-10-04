// Fill out your copyright notice in the Description page of Project Settings.


#include "Mine_GridSystem.h"
#include "MinesweepGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Mine_GameInstance.h"
#include "Mine_PlayerController.h"

// Sets default values
AMine_GridSystem::AMine_GridSystem()
{
	// remove tick
	PrimaryActorTick.bCanEverTick = false;
	// use the custom HUD class
	static ConstructorHelpers::FClassFinder<AMine_ActorTile> TileClass(TEXT("/Game/Blueprints/BP_Tile"));
	if (TileClass.Class != NULL)
	{
		tileBlueprint = TileClass.Class;
	}
}

// Called when the game starts or when spawned
void AMine_GridSystem::BeginPlay()
{
	Super::BeginPlay();
	CreateGrid();
}

// Creates a new grid based on gameInstance (gridSize,Difficulty)
void AMine_GridSystem::CreateGrid()
{
	// init
	gridScore = 0;
	hasGeneratedMines = false;
	gridWidth = 10;
	gridHeight = 10;
	mineCount = 10;
	// get gameinstance
	UMine_GameInstance* gameInstance = Cast<UMine_GameInstance>(GetGameInstance());
	if (gameInstance)
	{
		gridWidth = gameInstance->GetGridSize().X;
		gridHeight = gameInstance->GetGridSize().Y;
		// calculate the amount of mines there are in the grid based on diff - Easy = 10%, Normal = 15%, Hard = 20%
		mineCount = gridWidth * gridHeight;
		if (gameInstance->GetDifficulty() == Difficulty::Easy) mineCount = mineCount * 0.1f;
		if (gameInstance->GetDifficulty() == Difficulty::Norm) mineCount = mineCount * 0.15f;
		if (gameInstance->GetDifficulty() == Difficulty::Hard) mineCount = mineCount * 0.2f;
	}
	
	// only continue if the tileblueprint is set
	if (tileBlueprint == nullptr) return;
	// Build the grid array based on gridSize
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
	// reset the score
	gridScore = 0;
}

// Gererate the mines for the grid after the first click
void AMine_GridSystem::CreateMines(int clickX, int clickY)
{
	hasGeneratedMines = true;
	// create x * y array of ints
	TArray<TArray<int>> bombArray;
	for (int i = 0; i < gridWidth; i++)
	{
		TArray<int> bombValues;
		for (int j = 0; j < gridHeight; j++)
		{
			bombValues.Add(0);
		}
		bombArray.Add(bombValues);
	}
	// for each mine
	for (int i = 0; i < mineCount; i++)
	{
		// gernerate a random grid position
		int xLoc = FMath::RandRange(0, gridWidth-1);
		int yLoc = FMath::RandRange(0, gridHeight-1);
		// if the postion is the same as the clicked location, or is a mine already, dont add mine, and try again
		if (xLoc == clickX && yLoc == clickY || bombArray[xLoc][yLoc] > 8)	{i--; continue;}
		// add mine to location
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
	// update tile array with the new mine locations
	for (int y = 0; y < gridHeight; y++)
	{
		for (int x = 0; x < gridWidth; x++)
		{
			tileArray[x][y].SetMine(bombArray[x][y]);
		}
	}
}

// Reveal the tile to the player
void AMine_GridSystem::RevealTile(int x, int y)
{
	// check if the location is valid
	if (x > gridWidth - 1 || x <0 || y > gridHeight - 1 || y < 0) // x or y out of bounds
		return;
	// if we have not already generated the mines do so now
	if (!hasGeneratedMines)	CreateMines(x, y);
	// check if the tile is already revealed 
	if (!tileArray[x][y].isRevealed)
	{
		// update tile to be revealed, show the tile, if the tile is blank reveal the surrounding tiles
		tileArray[x][y].SetRevealed();
		tileArray[x][y].tile->ShowTile(tileArray[x][y].isMine, tileArray[x][y].mineWeight);
		if (tileArray[x][y].IsBlank())  RevealAdjacent(x, y); 
		// if the tile is a mine, end the game
		if (tileArray[x][y].IsMine()) 
		{ 
			RevealAll(); 
			AMinesweepGameModeBase* gameMode = Cast<AMinesweepGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
			gameMode->EndGame(false, gridScore);
			return;
		}
		// update the grid score
		gridScore++;
		//Check for win conditions
		CheckWin();
	}
	// update the controller hud with new score
	Cast<AMine_PlayerController>(GetWorld()->GetFirstPlayerController())->SetScore(gridScore);
}

// Reveal all the tiles in the grid
void AMine_GridSystem::RevealAll()
{
	for (int y = 0; y < gridHeight; y++)
	{
		for (int x = 0; x < gridWidth; x++)
		{
			tileArray[x][y].SetRevealed();
			tileArray[x][y].tile->ShowTile(tileArray[x][y].isMine, tileArray[x][y].mineWeight);
		}
	}
}

// tile was blank, reveal the surrounding tiles as well
void AMine_GridSystem::RevealAdjacent(int x, int y)
{
	// ensure the reveal tile is still in bounds
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

// Check for the win condition
void AMine_GridSystem::CheckWin()
{
	// check all tiles for being revealed (and not a bomb)
	for (int y = 0; y < gridHeight; y++)
	{
		for (int x = 0; x < gridWidth; x++)
		{
			if (!tileArray[x][y].isRevealed && !tileArray[x][y].IsMine()) return;
		}
	}
	// All non-mine tiles have been revealed, set level win
	AMinesweepGameModeBase* gameMode = Cast<AMinesweepGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	gameMode->EndGame(true, gridScore);


}

