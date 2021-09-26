// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Mine_MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class MINESWEEP_API UMine_MenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void DisableContinue();
	void SetTimer(float t);
	void SetScore(int s);
	void SetHeader(FString head);
	void SetStreak(int s);
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))	
	class UButton* Continue_Button;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Header;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Score;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* Timer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* GameStreak;
};
