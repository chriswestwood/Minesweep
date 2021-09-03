// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Mine_ActorTile.h"
#include "Mine_GridSystem.generated.h"

USTRUCT()
struct MINESWEEP_API FTileStruct
{
	GENERATED_BODY()

		AMine_ActorTile* tile;
		bool isMine;
		bool isRevealed;
		int mineWeight;

	void SetRevealed() { isRevealed = true; }
	void SetTile(AMine_ActorTile* t) { tile = t; }
	void SetMine(int m) { if (m >= 10 ? isMine = true : mineWeight = m)return; }
	bool IsBlank()
	{
		if (isMine) return false;
		return mineWeight == 0;
	}
	bool IsMine() { return isMine; }

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

	UPROPERTY(EditAnywhere, Category = Tile)
	TSubclassOf<class AMine_ActorTile> tileBlueprint;
	UPROPERTY(EditAnywhere, Category = Tile)
	int gridWidth;
	UPROPERTY(EditAnywhere, Category = Tile)
	int gridHeight;
	UPROPERTY(EditAnywhere, Category = Tile)
	int mineCount;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Create the initial grid of tiles
	void CreateGrid();
	// Set mine locations and numbers - x,y = the player tile selection
	void CreateMines(int clickX, int clickY);
	// Player selects tile - x,y = grid locations
	void RevealTile(int x, int y);
	void RevealAll(); // reveal all tiles
	// Check border tile, call RevealTile if it is
	void RevealAdjacent(int x, int y);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void CheckWin();
	TArray<TArray<FTileStruct>> tileArray;
	bool hasGeneratedMines;
	int gridScore;

};
