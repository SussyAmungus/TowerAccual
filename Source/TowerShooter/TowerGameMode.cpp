// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerGameMode.h"

ATowerGameMode::ATowerGameMode()
{

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ATowerGameMode::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);
}

void ATowerGameMode::BeginPlay()
{

	Super::BeginPlay();
}
