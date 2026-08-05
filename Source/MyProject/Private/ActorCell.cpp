// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorCell.h"

// Sets default values
AActorCell::AActorCell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;


	IsPlayerHere = false;
	Occupied = false;
	CellCenterLocation = GetActorLocation();

}

// Called when the game starts or when spawned
void AActorCell::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActorCell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

