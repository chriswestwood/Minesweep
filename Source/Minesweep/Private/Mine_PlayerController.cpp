// Fill out your copyright notice in the Description page of Project Settings.

#include "Mine_PlayerController.h"
#include "Mine_ActorTile.h"
#include "Mine_MenuWidget.h"
#include "Mine_LevelWidget.h"
#include "Mine_GameInstance.h"
#include "Kismet/GameplayStatics.h"

AMine_PlayerController::AMine_PlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Hand;
	static ConstructorHelpers::FClassFinder<UMine_LevelWidget> levelWidgetBPClass(TEXT("/Game/Blueprints/Mine_LevelWidgetBP"));
	if (levelWidgetBPClass.Class != NULL)
	{
		levelWidget = CreateWidget<UMine_LevelWidget>(GetWorld(), levelWidgetBPClass.Class);
	}
	static ConstructorHelpers::FClassFinder<UMine_MenuWidget> menuWidgetBPClass(TEXT("/Game/Blueprints/Mine_MenuWidgetBP"));
	if (menuWidgetBPClass.Class != NULL)
	{
		menuWidget = CreateWidget<UMine_MenuWidget>(GetWorld(), menuWidgetBPClass.Class);
	}

}

void AMine_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Select", IE_Pressed, this, &AMine_PlayerController::ClickTile);
	InputComponent->BindAction("Flag", IE_Pressed, this, &AMine_PlayerController::SetFlag);
	InputComponent->BindAction("Menu", IE_Pressed, this, &AMine_PlayerController::ViewMenu);
	InputComponent->BindAxis("MoveUp", this, &AMine_PlayerController::MoveUp);
	InputComponent->BindAxis("MoveRight", this, &AMine_PlayerController::MoveRight);

}

void AMine_PlayerController::ClickTile()
{
	if (bLevelOver || menuWidget->IsInViewport()) return;
	//Trace to see if anything is behind the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	if (Hit.bBlockingHit) {
		if (Hit.Actor != NULL) {
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

void AMine_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (levelWidget)
	{
		levelWidget->AddToViewport();
		levelWidget->SetScore(score);
		levelWidget->SetTimer(timer);
	}
	/*bLevelOver = true;
	if (bLevelOver) ViewMenu();*/
}

void AMine_PlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!menuWidget->IsInViewport())
	{
		timer += DeltaTime;
		if (levelWidget)
		{
			levelWidget->SetTimer(timer);
		}
	}
}

void AMine_PlayerController::ViewMenu()
{
	if (menuWidget)
	{
		if (!menuWidget->IsInViewport())
		{
			if (bLevelOver)
			{
				if (bGameWin) menuWidget->SetHeader("Congratulations");
				else menuWidget->SetHeader("Game Over");
			}
			menuWidget->SetTimer(timer);
			menuWidget->SetScore(score);
			menuWidget->SetStreak(Cast<UMine_GameInstance>(GetGameInstance())->GetGameStreak());
			menuWidget->AddToViewport();
			if (levelWidget) levelWidget->RemoveFromViewport();
			if (bLevelOver) menuWidget->DisableContinue();
		}
		else if (!bLevelOver)
		{
			menuWidget->RemoveFromViewport();
			if (levelWidget) levelWidget->AddToViewport();
		}
	}
}

void AMine_PlayerController::RestartGame()
{
	levelWidget->RemoveFromViewport();
	menuWidget->RemoveFromViewport();
	UGameplayStatics::OpenLevel(GetWorld(),"GameMap");
}

UMine_LevelWidget* AMine_PlayerController::getlevelWidget()
{
	return levelWidget;
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

void AMine_PlayerController::SetScore(int s)
{
	score = s;
	if (levelWidget) levelWidget->SetScore(score);
}

void AMine_PlayerController::SetGameEnd(int s, bool bWin)
{
	bLevelOver = true;
	bGameWin = bWin;
	if (bWin) Cast<UMine_GameInstance>(GetGameInstance())->IncreaseGameStreak();
	else  Cast<UMine_GameInstance>(GetGameInstance())->ResetGameStreak();
	SetScore(s);
	ViewMenu();
}
