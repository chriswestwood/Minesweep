// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Mine_ActorTile.h"
#include "Mine_GridSystem.generated.h"

// tile structure 
USTRUCT()
struct MINESWEEP_API FTileStruct
{
	GENERATED_BODY()
		// each tile has tile, mine flag, reveal flag, and amount of mines surrounding
		AMine_ActorTile* tile;
		bool isMine;
		bool isRevealed;
		int mineWeight;
	// Set tile to revealed
	void SetRevealed() { isRevealed = true; }
	// Set Tile
	void SetTile(AMine_ActorTile* t) { tile = t; }
	// Set tile to mine
	void SetMine(int m) { if (m >= 10 ? isMine = true : mineWeight = m)return; }
	// Check if the Tile is blank
	bool IsBlank()
	{
		if (isMine) return false;
		return mineWeight == 0;
	}
	// check if tile is a mine
	bool IsMine() { return isMine; }
	// init 
	FTileStruct()
	{ 
		isMine = false;
		isRevealed = false;
		mineWeight = 0;
	}
	
};

UCLASS()
class MINESWEEP_API AMine_GridSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMine_GridSystem();
	
	// Create the initial grid of tiles
	void CreateGrid();
	// Set mine locations and numbers - x,y = the player tile selection
	void CreateMines(int clickX, int clickY);
	// Player selects tile - x,y = grid locations
	void RevealTile(int x, int y);
	// Reveal all tiles to player
	void RevealAll(); 
	// Check border tile, call RevealTile if it is
	void RevealAdjacent(int x, int y);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Check win condition
	void CheckWin();
	// subclass of tile
	TSubclassOf<class AMine_ActorTile> tileBlueprint;
	// tile Array
	TArray<TArray<FTileStruct>> tileArray;
	// has the game generated mines
	bool hasGeneratedMines;
	// current grid values
	int gridScore;
	int gridWidth;
	int gridHeight;
	int mineCount;

};
