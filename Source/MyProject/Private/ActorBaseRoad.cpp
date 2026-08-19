

#include "ActorBaseRoad.h"
#include "DrawDebugHelpers.h"

DEFINE_LOG_CATEGORY(RoadLog);

AActorBaseRoad::AActorBaseRoad()
{

	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	BaseRoadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	BaseRoadMesh->SetupAttachment(RootComponent);

	RoadID = 0;
	StartSpawn = -500;
	EndSpawn = 500;
	CellStep = 100;

}


void AActorBaseRoad::BeginPlay()
{
	Super::BeginPlay();
	GeneratCells();
	
}

void AActorBaseRoad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

void AActorBaseRoad::GeneratCells()
{
	FVector SpawnLocation = GetActorLocation() + FVector(0, StartSpawn, 0);

	for (int i = 0; i < RoadLenght; i++)
	{
		FRotator SpawnRotation = FRotator::ZeroRotator;

		AActorCell* NewCell = GetWorld()->SpawnActor<AActorCell>(CellBP, SpawnLocation, SpawnRotation);

		if (NewCell)
		{
			UE_LOG(RoadLog, Log, TEXT("Created cell in %s"), *SpawnLocation.ToString());
			SpawnedCell.Add(NewCell);
			//DrawDebugPoint(GetWorld(), SpawnLocation + FVector(0, 0, 15), 10.f, FColor::Red, true, -1);
		}
		SpawnLocation += FVector(0, CellStep, 0);
	}

}

void AActorBaseRoad::DeleteCells()
{
	for (AActorCell* Cell : SpawnedCell)
	{
		if (IsValid(Cell))
		{
			//UE_LOG(RoadLog, Display, TEXT("Cell: %s has been destroyed"), *Cell->GetName());
			Cell->Destroy();
		}
	}
	SpawnedCell.Empty();
}

void AActorBaseRoad::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	DeleteCells();
}
