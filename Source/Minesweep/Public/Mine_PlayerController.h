// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Mine_PlayerController.generated.h"

/**
 *  Default Player Controller
 */
UCLASS()
class MINESWEEP_API AMine_PlayerController : public APlayerController
{
	GENERATED_BODY()


public:
	AMine_PlayerController();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	// View menu control
	UFUNCTION(BlueprintCallable, Category = Widget)
	void ViewMenu();
	// Restart game
	UFUNCTION(BlueprintCallable, Category = Game)
	void RestartGame();
	// get Level widget
	class UMine_LevelWidget* getlevelWidget();
	// sets
	void SetScore(int i);
	void SetGameEnd(int s, bool bWin);

protected:
	virtual void SetupInputComponent() override;
	// controls
	void ClickTile();
	void SetFlag();
	void MoveUp(float v);
	void MoveRight(float v);
	// widgets
	UPROPERTY()
	class UMine_LevelWidget* levelWidget;
	UPROPERTY()
	class UMine_MenuWidget* menuWidget;
	// vars
	int score;
	float timer;
	bool bLevelOver;
	bool bGameWin;
	
};
