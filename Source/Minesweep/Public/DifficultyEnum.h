// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "DifficultyEnum.generated.h"

UENUM()
enum Difficulty
{
	Easy    UMETA(DisplayName = "Easy"),
	Norm   UMETA(DisplayName = "Normal"),
	Hard   UMETA(DisplayName = "Hard")
};
/**
 * 
 */
UCLASS()
class MINESWEEP_API UDifficultyEnum : public UUserDefinedEnum
{
	GENERATED_BODY()
	
};
