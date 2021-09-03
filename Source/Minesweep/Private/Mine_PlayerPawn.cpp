// Fill out your copyright notice in the Description page of Project Settings.

#include "Mine_PlayerPawn.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"



// Sets default values
AMine_PlayerPawn::AMine_PlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// Our root component will be a sphere that reacts to physics
	USphereComponent* sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = sphereComp;
	sphereComp->InitSphereRadius(10.0f);
	sphereComp->SetCollisionProfileName(TEXT("Pawn"));

	UCameraComponent* camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ActualCamera"));
	camera->SetupAttachment(sphereComp, USpringArmComponent::SocketName);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AMine_PlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMine_PlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMine_PlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

