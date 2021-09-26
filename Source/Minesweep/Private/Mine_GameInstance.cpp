// Fill out your copyright notice in the Description page of Project Settings.


#include "Mine_GameInstance.h"

void UMine_GameInstance::Init()
{
	gridSize = FVector2D(10, 10);
	ResetLevelScore();
	gameDiff = Difficulty::Easy;
}

void UMine_GameInstance::SetDifficulty(Difficulty d)
{
	gameDiff = d;
}

void UMine_GameInstance::IncreaseLevelScore(int i)
{
	levelScore += i;
}

void UMine_GameInstance::ResetLevelScore()
{
	levelScore = 0;
}

void UMine_GameInstance::SetGridSize(int x, int y)
{
	SetGridSize(FVector2D(x, y));
}

void UMine_GameInstance::SetGridSize(FVector2D g)
{
	gridSize = g;
	if (gridSize.X < 1) gridSize.X = 1;
	if (gridSize.Y < 1) gridSize.Y = 1;
}

int UMine_GameInstance::GetLevelScore()
{
	return levelScore;
}

FVector2D UMine_GameInstance::GetGridSize()
{
	return gridSize;
}

Difficulty UMine_GameInstance::GetDifficulty()
{
	return gameDiff;
}

void UMine_GameInstance::IncreaseGameStreak()
{
	GameStreak++;
}
void UMine_GameInstance::ResetGameStreak()
{
	GameStreak = 0;
}
int UMine_GameInstance::GetGameStreak()
{
	return GameStreak;
}