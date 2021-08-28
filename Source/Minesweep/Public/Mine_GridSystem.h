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
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Create the initial grid of tiles
	void CreateGrid(int x, int y);
	// Set mine locations and numbers - x,y = the player tile selection
	void CreateMines(int x, int y);
	// Player selects tile - x,y = grid locations
	void RevealTile(int x, int y);
	// Check border tile, call RevealTile if it is
	void CheckAdjacent(int x, int y);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	int width;
	int height;
	int mineCount;
	TArray<TArray<FTileStruct>> tileArray;

	//TEST





};
