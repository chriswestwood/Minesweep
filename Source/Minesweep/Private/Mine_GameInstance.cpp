// Fill out your copyright notice in the Description page of Project Settings.


#include "Mine_GameInstance.h"

// Initalise Game Instance
void UMine_GameInstance::Init()
{
	gridSize = FVector2D(10, 10);
	ResetLevelScore();
	gameDiff = Difficulty::Easy;
}

// Change the Difficulty
void UMine_GameInstance::SetDifficulty(Difficulty d)
{
	gameDiff = d;
}

// Add i to current LevelScore
void UMine_GameInstance::IncreaseLevelScore(int i)
{
	levelScore += i;
}

// Set levelScore to 0
void UMine_GameInstance::ResetLevelScore()
{
	levelScore = 0;
}

// Call SetGridSize(FVector)
void UMine_GameInstance::SetGridSize(int x, int y)
{
	SetGridSize(FVector2D(x, y));
}

// Set the Grid Size
void UMine_GameInstance::SetGridSize(FVector2D g)
{
	gridSize = g;
	// ensur the size is at least 1 by 1
	if (gridSize.X < 1) gridSize.X = 1;
	if (gridSize.Y < 1) gridSize.Y = 1;
}

// retrieve the levelScore
int UMine_GameInstance::GetLevelScore()
{
	return levelScore;
}

// Retrieve gridSize
FVector2D UMine_GameInstance::GetGridSize()
{
	return gridSize;
}

// Retrieve gameDiff
Difficulty UMine_GameInstance::GetDifficulty()
{
	return gameDiff;
}

// Increase the GameStreak
void UMine_GameInstance::IncreaseGameStreak()
{
	GameStreak++;
}

// Set GameStreak to 0
void UMine_GameInstance::ResetGameStreak()
{
	GameStreak = 0;
}

// Retrieve the GameStreak
int UMine_GameInstance::GetGameStreak()
{
	return GameStreak;
}