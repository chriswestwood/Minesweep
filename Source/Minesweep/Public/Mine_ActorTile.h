// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Mine_ActorTile.generated.h"

UCLASS()
class MINESWEEP_API AMine_ActorTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMine_ActorTile();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Update the tile to show if mine / or weight of tile 
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Reveal"))
	void ShowTile(bool m, int c);
	// Update the tile to show if mine / or weight of tile 
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Flag"))
	void FlagTile(bool f);
	// tile is clicked by player
	void ClickTile();
	// tile is flagged by player
	void ChangeFlag();

	void SetPos(int x, int y);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "settings")
		bool isFlagged;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "settings")
		bool isClicked;

private:	
	int xLoc;
	int yLoc;

};
