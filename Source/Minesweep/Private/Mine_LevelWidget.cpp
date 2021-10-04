// Fill out your copyright notice in the Description page of Project Settings.


#include "Mine_LevelWidget.h"
#include "Components/TextBlock.h"

void UMine_LevelWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

// Set timer 
void UMine_LevelWidget::SetTimer(float time)
{
	if(TimerText) TimerText->SetText(FText::AsNumber(time));
}

// Set score
void UMine_LevelWidget::SetScore(int score)
{
	if (ScoreText) ScoreText->SetText(FText::AsNumber(score));
}

