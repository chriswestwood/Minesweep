// Fill out your copyright notice in the Description page of Project Settings.

#include "Mine_PlayerController.h"
#include "Mine_ActorTile.h"


AMine_PlayerController::AMine_PlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Hand;
}

void AMine_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Select", IE_Pressed, this, &AMine_PlayerController::ClickTile);
	InputComponent->BindAction("Flag", IE_Pressed, this, &AMine_PlayerController::SetFlag);
	InputComponent->BindAxis("MoveUp", this, &AMine_PlayerController::MoveUp);
	InputComponent->BindAxis("MoveRight", this, &AMine_PlayerController::MoveRight);

}

void AMine_PlayerController::ClickTile()
{

	//Trace to see if anything is behind the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	if (Hit.bBlockingHit) {
		if (Hit.Actor != NULL) {
			UE_LOG(LogTemp, Warning, TEXT("Reveal"));
			AMine_ActorTile* selected = Cast<AMine_ActorTile>(Hit.GetActor());
			selected->ClickTile();
		}
	}

}

void AMine_PlayerController::SetFlag()
{
	//Trace to see if anything is behind the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	if (Hit.bBlockingHit) {
		if (Hit.Actor != NULL) {
			UE_LOG(LogTemp, Warning, TEXT("Flag"));
			AMine_ActorTile* selected = Cast<AMine_ActorTile>(Hit.GetActor());
			selected->ChangeFlag();
		}
	}
}

void AMine_PlayerController::MoveUp(float v)
{	
	if (v != 0.0f)
	{
		GetPawn()->AddActorWorldOffset(FVector(0, 0, v * 10), false);
	}
}

void AMine_PlayerController::MoveRight(float v)
{
	if (v != 0.0f)
	{
		GetPawn()->AddActorWorldOffset(FVector(v * 10, 0, 0), false);
	}
}
