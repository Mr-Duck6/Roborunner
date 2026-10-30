
#include "ActorGeneratorMap.h"
#include "ActorSafeRoad.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(GeneratorMapLog);


AActorGeneratorMap::AActorGeneratorMap()
{
	PrimaryActorTick.bCanEverTick = true;

	//Counters
	SafeRoadCounter = 0;
	DangerRoadCounter = 0;

	ChoicedRoad = 0;
	SpawnRoadLocation = GetActorLocation();

	NextRoadID = 0;

}

void AActorGeneratorMap::BeginPlay()
{
	Super::BeginPlay();
	
	//Spawn first 30 roads
	NextTriggerLocation = StartSpawnThreshold + 1; 

	for (int32 i = 0; i < InitialQuantityRoad; i++)
	{
		SpawnRoad();
	}
	
}

void AActorGeneratorMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PlayerProgression();

}


void AActorGeneratorMap::SpawnRoad()
{
	UE_LOG(GeneratorMapLog, Display, TEXT("FUNCTION SpawnRoad called"));

	if (FirstRoadsCounter < FirstRoads)
	{
		FirstRoadsCounter++;
		SpawnFirstRoad();
		return;
	}

	FRotator SpawnRotation = FRotator::ZeroRotator;

	ChoiceRoadToSpawn();

	if (AllBPRoads.IsValidIndex(ChoicedRoad))
	{
		TSubclassOf<AActorBaseRoad> SelectedClass = AllBPRoads[ChoicedRoad];
		if (SelectedClass != nullptr)
		{
			AActorBaseRoad* NewRoad = GetWorld()->SpawnActor<AActorBaseRoad>(SelectedClass, SpawnRoadLocation, SpawnRotation);
			if (NewRoad)
			{
				NewRoad->RoadID = NextRoadID;
				NextRoadID++;

				UE_LOG(GeneratorMapLog, Display, TEXT("New road %i has been spawned in %s, Road %s"),
					NewRoad->RoadID,
					*SpawnRoadLocation.ToString(),
					*UEnum::GetValueAsString(NewRoad->RoadType));

				SpawnedRoad.Add(NewRoad);
				SpawnRoadLocation += StepToSpawn;
				NewRoad->RoadID++;
			}
		}
	}
}

void AActorGeneratorMap::DeleteRoad()
{
	UE_LOG(GeneratorMapLog,Display,TEXT("FUNCTION DeleteRoad called"));

	if (SpawnedRoad.IsValidIndex(0))
	{
		auto CurrentRoad = SpawnedRoad[0];

		if (CurrentRoad != nullptr)
		{
			UE_LOG(GeneratorMapLog, Display, TEXT("Road %s has been deleted"), *SpawnedRoad[0]->GetName());
			SpawnedRoad[0]->Destroy();
		}
		SpawnedRoad.RemoveAt(0);
	}
}


int32 AActorGeneratorMap::ChoiceRoadToSpawn()
{
	UE_LOG(GeneratorMapLog, Display, TEXT("FUNCTION ChoiceRoadToSpawn called"));

	ChoicedRoad = FMath::RandRange(0, AllBPRoads.Num()-1);

	//Rule for turret road spawn (only after safe road)
	if (ChoicedRoad == 2)
	{
		if (!SpawnedRoad.IsEmpty() && SpawnedRoad.Last()->IsA(AActorSafeRoad::StaticClass()))
		{
			return ChoicedRoad = 2;
		}
		else
		{
			ChoicedRoad = 1;
		}
	}
	UE_LOG(GeneratorMapLog, Display, TEXT("Chosed num is %i, road for spawn is: %s"), ChoicedRoad, *GetNameSafe(AllBPRoads[ChoicedRoad]));

	//Limits
	if(SafeRoadCounter == MaxSafeRoadInRow)
	{
		UE_LOG(GeneratorMapLog, Display, TEXT("Use of an exception: SafeRoadCounter == MaxSafeRoadInRow, SafeRoadCounter is: %i  "), SafeRoadCounter);
		ChoicedRoad = 1;
	}
	else if (DangerRoadCounter == MaxDangerRoadInRow)
	{ 
		UE_LOG(GeneratorMapLog, Display, TEXT("Use of an exception: DangerRoadCounter == MaxDangerRoadInRow, DangerRoadCounter is: %i  "), DangerRoadCounter);
		ChoicedRoad = 0;
	}

	//Case spawn
	switch (ChoicedRoad)
	{
	
	case 0://Safe road
		UE_LOG(GeneratorMapLog, Display, TEXT
		("Called case 0:\n SafeRoadCounter: %d\n DangerRoadCounter: %d\n Returned ChoicedRoad: %d"),
			SafeRoadCounter, DangerRoadCounter, ChoicedRoad);

		SafeRoadCounter++;
		DangerRoadCounter = 0;
		return ChoicedRoad;

	case 1://Danger road
		UE_LOG(GeneratorMapLog, Display, TEXT("Called case 1:\n SafeRoadCounter: %d\n DangerRoadCounter: %d\n Returned ChoicedRoad: %d"),
		SafeRoadCounter, DangerRoadCounter, ChoicedRoad);

		DangerRoadCounter++;
		SafeRoadCounter = 0;
		return ChoicedRoad;

	case 2://Turret road
		UE_LOG(GeneratorMapLog, Display, TEXT
		("Called case 2:\n SafeRoadCounter: %d\n DangerRoadCounter: %d\n Returned ChoicedRoad: %d"),
			SafeRoadCounter, DangerRoadCounter, ChoicedRoad);

		SafeRoadCounter = 0;
		DangerRoadCounter = 0;
		return ChoicedRoad;

	default:

		UE_LOG(GeneratorMapLog, Display, TEXT
		("Called default case:\n SafeRoadCounter: %d\n DangerRoadCounter: %d\n Returned ChoicedRoad: %d"),
			SafeRoadCounter, DangerRoadCounter, ChoicedRoad);

		ChoicedRoad = 0;
		SafeRoadCounter++;
		DangerRoadCounter = 0;
		return ChoicedRoad;
	}
}

void AActorGeneratorMap::SpawnFirstRoad()
{
	UE_LOG(GeneratorMapLog, Display, TEXT("Function SpawnFirstRoad called"));
	FRotator SpawnRotation = FRotator::ZeroRotator;

	if (IsValid(FirstRoadBP))
	{
		AActorBaseRoad* NewRoad = GetWorld()->SpawnActor<AActorBaseRoad>(FirstRoadBP, SpawnRoadLocation, SpawnRotation);
		if (NewRoad)
		{
			NewRoad->RoadID = NextRoadID;
			NextRoadID++;

			UE_LOG(GeneratorMapLog, Display, TEXT("New road %i has been spawned in %s, Road %s"),
				NewRoad->RoadID,
				*SpawnRoadLocation.ToString(),
				*UEnum::GetValueAsString(NewRoad->RoadType));

				SpawnedRoad.Add(NewRoad);
				SpawnRoadLocation += StepToSpawn;
				NewRoad->RoadID++;
		}
	}
}

void AActorGeneratorMap::PlayerProgression()
{
	APawnPlayer* Player = Cast<APawnPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(),APawnPlayer::StaticClass()));

	if (Player)
	{
		if (Player->PlayerRoadLocation >= NextTriggerLocation)
		{
			NextTriggerLocation++;
			SpawnRoad();
			DeleteRoad();
		}
	}
}

AActorBaseRoad* AActorGeneratorMap::GetRoadByID(int32 TargetID)
{
	for (AActorBaseRoad* Road : SpawnedRoad)
	{
		if (IsValid(Road) && Road->RoadID == TargetID)
		{
			return Road;
		}
	}
	return nullptr;
}