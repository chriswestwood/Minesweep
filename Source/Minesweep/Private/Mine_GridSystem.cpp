// Fill out your copyright notice in the Description page of Project Settings.


#include "Mine_GridSystem.h"

// Sets default values
AMine_GridSystem::AMine_GridSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMine_GridSystem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMine_GridSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMine_GridSystem::CreateGrid(int x,int y)
{
	// init array
	// for x
		//  for y
			// create struct
			// set tile x,y
	FVector location;
	FRotator rotation;
	FActorSpawnParameters spawnParam;
	AMine_ActorTile* tile = GetWorld()->SpawnActor<AMine_ActorTile>(tileBlueprint, location, rotation, spawnParam);
}

void AMine_GridSystem::CreateMines(int x, int y)
{
}

void AMine_GridSystem::RevealTile(int x, int y)
{

}

void AMine_GridSystem::CheckAdjacent(int x, int y)
{
}

