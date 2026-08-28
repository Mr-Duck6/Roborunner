
#include "ActorGeneratorMap.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(GeneratorMapLog);


AActorGeneratorMap::AActorGeneratorMap()
{
	PrimaryActorTick.bCanEverTick = true;

	SafeRoadCounter = 0;
	DangerRoadCounter = 0;
	TurrelRoadCounter = 0;

	ChoicedRoad = 0;
	SpawnRoadLocation = GetActorLocation();

	NextRoadID = 0;

}

void AActorGeneratorMap::BeginPlay()
{
	Super::BeginPlay();


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
	UE_LOG(GeneratorMapLog, Display, TEXT("Chosed num is %i, road for spawn is: %s"), ChoicedRoad, *GetNameSafe(AllBPRoads[ChoicedRoad]));


	if(SafeRoadCounter == MaxSafeRoadInRow)//Limits
	{
		UE_LOG(GeneratorMapLog, Display, TEXT("Use of an exception: SafeRoadCounter == MaxSafeRoadInRow, SafeRoadCounter is: %i  "), SafeRoadCounter);
		ChoicedRoad = 1;
	}
	else if (DangerRoadCounter == MaxDangerRoadInRow)
	{ 
		UE_LOG(GeneratorMapLog, Display, TEXT("Use of an exception: DangerRoadCounter == MaxDangerRoadInRow, DangerRoadCounter is: %i  "), DangerRoadCounter);
		ChoicedRoad = 0;
	}
	else if (TurrelRoadCounter == MaxTurrelRoadInRow)
	{
		UE_LOG(GeneratorMapLog, Display, TEXT("Use of an exception: TurrelRoadCounter == MaxTurrelRoadInRow, TurrelRoadCounter is: %i  "), TurrelRoadCounter);
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