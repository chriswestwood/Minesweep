// Fill out your copyright notice in the Description page of Project Settings.

#include "Mine_ActorTile.h"

// Sets default values
AMine_ActorTile::AMine_ActorTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMine_ActorTile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMine_ActorTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMine_ActorTile::ClickTile()
{
	if (!isClicked)
	{
		isClicked = true;
		// TODO: call grid system reveal tile
	}
}