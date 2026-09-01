

#include "ActorTurretRoad.h"
#include "ActorTurret.h"

AActorTurretRoad::AActorTurretRoad()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AActorTurretRoad::BeginPlay()
{
	Super::BeginPlay();
	SpawnTurret();
}

void AActorTurretRoad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AActorTurretRoad::SpawnTurret()
{
	UE_LOG(RoadLog, Display, TEXT("Function SpawnTurret called"));
	FVector SpawnLocation = GetActorLocation() - FVector(0, 600, 0);
	FRotator SpawnRotation = FRotator::ZeroRotator;

	Turret = GetWorld()->SpawnActor<AActorTurret>(TurretBP,SpawnLocation,SpawnRotation);
}

void AActorTurretRoad::DeleteTurret()
{
	UE_LOG(RoadLog, Display, TEXT("Function DeleteTurret called"));
	if (IsValid(Turret))
	{
		Turret->Destroy();
		Turret = nullptr;
	}
}

void AActorTurretRoad::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	DeleteTurret();
}