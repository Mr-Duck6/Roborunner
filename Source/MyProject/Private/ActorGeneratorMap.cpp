

#include "ActorGeneratorMap.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(GeneratorMapLog);


AActorGeneratorMap::AActorGeneratorMap()
{
	PrimaryActorTick.bCanEverTick = false;

	SafeRoadCounter = 0;
	DangerRoadCounter = 0;
	TurrelRoadCounter = 0;

	ChoicedRoad = 0;
	CanBeDeleted = false;
	SpawnRoadLocation = GetActorLocation() - FVector(0,0,60);
	DistanceBetweenFence = {200,0,0};


}

void AActorGeneratorMap::BeginPlay()
{
	Super::BeginPlay();


	for (int32 i = 0; i < InitialQuantityRoad; i++)
	{
		SpawnRoad();
	}

	
}

void AActorGeneratorMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AActorGeneratorMap::SpawnRoad()
{
	FRotator SpawnRotation = FRotator::ZeroRotator;
	FVector StepToSpawn = { 100, 0, 0 };

	ChoiceRoadToSpawn();

	if (AllBPRoads.IsValidIndex(ChoicedRoad))
	{
		TSubclassOf<AActorBaseRoad> SelectedClass = AllBPRoads[ChoicedRoad];
		if (SelectedClass != nullptr)
		{
			AActorBaseRoad* NewRoad = GetWorld()->SpawnActor<AActorBaseRoad>(SelectedClass, SpawnRoadLocation, SpawnRotation);
			if (NewRoad)
			{
				UE_LOG(GeneratorMapLog, Display, TEXT("New road %i has been spawned in %s"), NewRoad->RoadID,*SpawnRoadLocation.ToString());
				SpawnedRoad.Add(NewRoad);
				SpawnRoadLocation += StepToSpawn;
				NewRoad->RoadID++;
			}
		}
	}

	if (CanBeDeleted)
	{
		UE_LOG(GeneratorMapLog, Display, TEXT("CanBeDeleted is %s"),CanBeDeleted? TEXT("true") : TEXT("false"));
		DeleteRoad();
	}
}


void AActorGeneratorMap::DeleteRoad()
{
	if (SpawnedRoad.IsValidIndex(0))
	{
		if (IsValid(SpawnedRoad[0]))
		{
			UE_LOG(GeneratorMapLog, Display, TEXT("Road %s has been deleted"), *SpawnedRoad[0]->GetName());
			SpawnedRoad[0]->Destroy();
		}
		SpawnedRoad.RemoveAt(0);
	}
	DeleteFence();
}


int32 AActorGeneratorMap::ChoiceRoadToSpawn()
{
	int32 MaxSafeRoadInRow = 3;
	int32 MaxDangerRoadInRow = 4;
	int32 MaxTurrelRoadInRow = 2;

	ChoicedRoad = FMath::RandRange(0, 2);
	UE_LOG(GeneratorMapLog, Display, TEXT("Generated num is: %i"), ChoicedRoad);

	if(SafeRoadCounter == MaxSafeRoadInRow)//Limits
	{
		UE_LOG(GeneratorMapLog, Display, TEXT("SafeRoadCounted is: %i"), SafeRoadCounter);
		ChoicedRoad = 1;
	}
	else if (DangerRoadCounter == MaxDangerRoadInRow)
	{ 
		UE_LOG(GeneratorMapLog, Display, TEXT("DangerRoadCounter is: %i"), DangerRoadCounter);
		ChoicedRoad = 0;
	}
	else if (TurrelRoadCounter == MaxTurrelRoadInRow)
	{
		UE_LOG(GeneratorMapLog, Display, TEXT("TurrelRoadCounter is: %i"), TurrelRoadCounter);
		ChoicedRoad = 0;
	}

	switch (ChoicedRoad)//Case spawn
	{

	case 0:
		UE_LOG(GeneratorMapLog, Display, TEXT
		("Called case 0:\n SafeRoadCounter: %d\n DangerRoadCounter: %d\n TurrelRoadCounter: %d\n Returned ChoicedRoad: %d"),
			SafeRoadCounter, DangerRoadCounter, TurrelRoadCounter, ChoicedRoad);

		SafeRoadCounter++;
		DangerRoadCounter = 0;
		TurrelRoadCounter = 0;
		return ChoicedRoad;

	case 1:UE_LOG(GeneratorMapLog, Display, TEXT
		  ("Called case 1:\n SafeRoadCounter: %d\n DangerRoadCounter: %d\n TurrelRoadCounter: %d\n Returned ChoicedRoad: %d"),
		SafeRoadCounter, DangerRoadCounter, TurrelRoadCounter, ChoicedRoad);

		DangerRoadCounter++;
		SafeRoadCounter = 0;
		TurrelRoadCounter = 0;
		return ChoicedRoad;

	case 2:
		UE_LOG(GeneratorMapLog, Display, TEXT
		("Called case 2:\n SafeRoadCounter: %d\n DangerRoadCounter: %d\n TurrelRoadCounter: %d\n Returned ChoicedRoad: %d"),
			SafeRoadCounter, DangerRoadCounter, TurrelRoadCounter, ChoicedRoad);

		TurrelRoadCounter++;
		SafeRoadCounter = 0;
		DangerRoadCounter = 0;
		return ChoicedRoad;

	default:

		UE_LOG(GeneratorMapLog, Display, TEXT
		("Called default case:\n SafeRoadCounter: %d\n DangerRoadCounter: %d\n TurrelRoadCounter: %d\n Returned ChoicedRoad: %d"),
			SafeRoadCounter, DangerRoadCounter, TurrelRoadCounter, ChoicedRoad);

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

void AActorGeneratorMap::SpawnFence(FVector SpawnLocation)
{
	
}


void AActorGeneratorMap::DeleteFence()
{
	for (int i=0;i<SpawnedFence.Num()-1;i++)
	{
		if (SpawnedFence.IsValidIndex(i))
		{
			auto CurrentFance = SpawnedFence[i];

			if (CurrentFance != nullptr)
			{
				SpawnedFence[i]->Destroy();
				SpawnedFence.RemoveAt(i);
			}
		}
	}
		SpawnedFence.Empty();
}