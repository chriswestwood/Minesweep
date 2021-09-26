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
	UFUNCTION(BlueprintCallable, Category = Settings)
	void SetDifficulty(Difficulty d);
	void IncreaseLevelScore(int i);
	UFUNCTION(BlueprintCallable, Category = Settings)
	void ResetLevelScore();
	UFUNCTION(BlueprintCallable, Category = Settings)
	void SetGridSize(int x, int y);
	void SetGridSize(FVector2D g);
	UFUNCTION(BlueprintCallable, Category = Settings)
	int GetLevelScore();
	FVector2D GetGridSize();
	Difficulty GetDifficulty();
	void IncreaseGameStreak();
	void ResetGameStreak();
	int GetGameStreak();

protected:

	int levelScore;
	FVector2D gridSize;
	Difficulty gameDiff;
	int GameStreak;
};
