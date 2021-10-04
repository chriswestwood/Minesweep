// Fill out your copyright notice in the Description page of Project Settings.


#include "Mine_MenuWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

// Disable the Continue button if the current game is over
void UMine_MenuWidget::DisableContinue()
{
	if (Continue_Button) Continue_Button->SetVisibility(ESlateVisibility::Hidden);
}

// Set Timer
void UMine_MenuWidget::SetTimer(float t)
{
	Timer->SetText(FText::AsNumber(t));
}

// Set Timer
void UMine_MenuWidget::SetScore(int s)
{
	Score->SetText(FText::AsNumber(s));
}

// Set Header
void UMine_MenuWidget::SetHeader(FString head)
{
	Header->SetText(FText::FromString(head));
}

// Set Streak
void UMine_MenuWidget::SetStreak(int s)
{
	GameStreak->SetText(FText::AsNumber(s));
}