// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Mine_LevelWidget.generated.h"

/**
 *  Displays the current game status of timer and score
 */
UCLASS()
class MINESWEEP_API UMine_LevelWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	// Sets
	void SetTimer(float time);
	void SetScore(int increase);

	// Screen values
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* TimerText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		class UTextBlock* ScoreText;

};
