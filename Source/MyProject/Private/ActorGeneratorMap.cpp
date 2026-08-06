

#include "ActorGeneratorMap.h"
#include "Kismet/GameplayStatics.h"


AActorGeneratorMap::AActorGeneratorMap()
{
	PrimaryActorTick.bCanEverTick = true;

	SafeRoadCounter = 0;
	DangerRoadCounter = 0;
	TurrelRoadCounter = 0;

	ChoicedRoad = 0;
	CanBeDeleted = false;

}

void AActorGeneratorMap::BeginPlay()
{
	Super::BeginPlay();
	
}

void AActorGeneratorMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AActorGeneratorMap::SpawnRoad()
{
	FVector SpawnLocation = { 0,0,0 };
	FRotator SpawnRotation = FRotator::ZeroRotator;
	FVector StepToSpawn = { 100, 0, 0 };

	ChoiceRoadToSpawn();

	if (AllBPRoads.IsValidIndex(ChoicedRoad))
	{
		TSubclassOf<AActorBaseRoad> SelectedClass = AllBPRoads[ChoicedRoad];
		if (SelectedClass != nullptr)
		{
			AActorBaseRoad* NewRoad = GetWorld()->SpawnActor<AActorBaseRoad>(SelectedClass, SpawnLocation, SpawnRotation);
			if (NewRoad)
			{
				SpawnedRoad.Add(NewRoad);
			}
		}
	}

	if (CanBeDeleted)
	{
		DeleteRoad();
	}
}


void AActorGeneratorMap::DeleteRoad()
{
	if (SpawnedRoad.IsValidIndex(0))
	{
		if (IsValid(SpawnedRoad[0]))
		{
			SpawnedRoad[0]->Destroy();
		}
		SpawnedRoad.RemoveAt(0);
	}
}


int32 AActorGeneratorMap::ChoiceRoadToSpawn()
{
	int32 MaxSafeRoadInRow = 3;
	int32 MaxDangerRoadInRow = 4;
	int32 MaxTurrelRoadInRow = 2;

	ChoicedRoad = FMath::RandRange(0, 2);

	if(SafeRoadCounter == MaxSafeRoadInRow)//Limits
	{
		ChoicedRoad = 1;
	}
	else if (DangerRoadCounter == MaxDangerRoadInRow)
	{ 
		ChoicedRoad = 0;
	}
	else if (TurrelRoadCounter == MaxTurrelRoadInRow)
	{
		ChoicedRoad = 0;
	}

	switch (ChoicedRoad)//Case spawn
	{

	case 0:
		SafeRoadCounter++;
		DangerRoadCounter = 0;
		TurrelRoadCounter = 0;
		return ChoicedRoad;

	case 1:
		DangerRoadCounter++;
		SafeRoadCounter = 0;
		TurrelRoadCounter = 0;
		return ChoicedRoad;

	case 2:
		TurrelRoadCounter++;
		SafeRoadCounter = 0;
		DangerRoadCounter = 0;
		return ChoicedRoad;

	default:
		ChoicedRoad = 0;
		SafeRoadCounter++;
		DangerRoadCounter = 0;
		TurrelRoadCounter = 0;
		return ChoicedRoad;
	}
}

void AActorGeneratorMap::PlayerProgression()
{
	APawnPlayer* Player = Cast<APawnPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Player)
	{
		if (Player->PlayerRoadLocation > 15)
		{
			CanBeDeleted = true;
		}
	}
}