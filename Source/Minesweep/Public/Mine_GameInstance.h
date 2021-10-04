// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DifficultyEnum.h"
#include "Mine_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MINESWEEP_API UMine_GameInstance : public UGameInstance
{
	GENERATED_BODY()

	virtual void Init() override;
public:
	// Set game diff
	UFUNCTION(BlueprintCallable, Category = Settings)
	void SetDifficulty(Difficulty d);
	// Increase the levelScore by i
	void IncreaseLevelScore(int i);
	// Reset levelScore to 0
	UFUNCTION(BlueprintCallable, Category = Settings)
	void ResetLevelScore();
	// set grid Size
	UFUNCTION(BlueprintCallable, Category = Settings)
	void SetGridSize(int x, int y);
	void SetGridSize(FVector2D g);
	// Get levelScore
	UFUNCTION(BlueprintCallable, Category = Settings)
	int GetLevelScore();
	// Get GridSize
	FVector2D GetGridSize();
	// Get Difficulty
	Difficulty GetDifficulty();
	// increase game Streak by 1
	void IncreaseGameStreak();
	// Set GameStreak to 0
	void ResetGameStreak();
	// Get GameStreak
	int GetGameStreak();

protected:

	// current level score
	int levelScore;
	// current level gridSize
	FVector2D gridSize;
	// current level difficutlty
	Difficulty gameDiff;
	// current game streak
	int GameStreak;
};
