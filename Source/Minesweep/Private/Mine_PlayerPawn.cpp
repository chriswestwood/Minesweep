// Fill out your copyright notice in the Description page of Project Settings.

#include "Mine_PlayerPawn.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"



// Set default values
AMine_PlayerPawn::AMine_PlayerPawn()
{
 	// remove tick
	PrimaryActorTick.bCanEverTick = false;
	// add root comp
	USphereComponent* sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = sphereComp;
	sphereComp->InitSphereRadius(10.0f);
	sphereComp->SetCollisionProfileName(TEXT("Pawn"));
	// add camera comp
	UCameraComponent* camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));
	camera->SetupAttachment(sphereComp, USpringArmComponent::SocketName);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AMine_PlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void AMine_PlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

