

#include "ActorCell.h"

AActorCell::AActorCell()
{
 
	PrimaryActorTick.bCanEverTick = false;


	IsPlayerHere = false;
	Occupied = false;

}


void AActorCell::BeginPlay()
{
	Super::BeginPlay();
	CellCenterLocation = GetActorLocation();
	
}


void AActorCell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

