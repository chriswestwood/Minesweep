// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Mine_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MINESWEEP_API AMine_PlayerController : public APlayerController
{
	GENERATED_BODY()


public:
	AMine_PlayerController();

protected:
	virtual void SetupInputComponent() override;

	void ClickTile();
	void SetFlag();
	void MoveUp(float v);
	void MoveRight(float v);
	
};