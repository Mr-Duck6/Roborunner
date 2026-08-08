

#include "ActorSafeRoad.h"
#include "Kismet/GameplayStatics.h"
#include "ActorGeneratorMap.h"


AActorSafeRoad::AActorSafeRoad()
{
	PrimaryActorTick.bCanEverTick = false;

	SpawnedObjectsCounter = 0;
}

void AActorSafeRoad::BeginPlay()
{
	Super::BeginPlay();

	SpawnObject();


}

void AActorSafeRoad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AActorSafeRoad::SpawnObject()
{
    for (int32 i = 0; i < SpawnedCell.Num(); i++)
    {
        bool bCreateObject = FMath::RandBool();

		if (SpawnedObjectsCounter >= MaxObjectsInRow)//Limit to spawn in one row
		{
			SpawnedObjectsCounter = 0;
			return;
		}

        if (bCreateObject && IsValid(SpawnedCell[i]))
        {
            int32 SelectedIndex = ChoiceObjectToSpawn();

            if (AllBPObject.IsValidIndex(SelectedIndex) && AllBPObject[SelectedIndex])
            {
                FVector SpawnLocation = SpawnedCell[i]->CellCenterLocation;
                FRotator SpawnRotation = FRotator::ZeroRotator;

                AActorBaseObject* NewObject = GetWorld()->SpawnActor<AActorBaseObject>(AllBPObject[SelectedIndex],SpawnLocation,
                    SpawnRotation);

                if (NewObject)
                {
                    UE_LOG(RoadLog, Log, TEXT("Spawned %s object in %s."), *NewObject->GetName(), *SpawnLocation.ToString());
                    SpawnedObjects.Add(NewObject);
					SpawnedCell[i]->Occupied = true;
					SpawnedObjectsCounter++;
                }
            }
        }
    }
}

void AActorSafeRoad::DeleteObjects()
{
	for (int32 i=0 ;i<RoadLenght; i++)
	{
		if (SpawnedObjects.IsValidIndex(i))
		{
			auto CurrentObject = SpawnedObjects[i];
			if (CurrentObject != nullptr)
			{
				UE_LOG(RoadLog, Log, TEXT("Delete object: %s"), *CurrentObject->GetName());
				CurrentObject->Destroy();
				SpawnedObjects.RemoveAt(i);
			}
		}
	}
	SpawnedObjects.Empty();
}

int32 AActorSafeRoad::ChoiceObjectToSpawn()//Choise object to spawn (now only fence)
{
	ChoicedObject = FMath::RandRange(0, AllBPObject.Num() - 1);
	UE_LOG(RoadLog, Log, TEXT("Choice object: %s"), *AllBPObject[ChoicedObject]->GetName());
	return ChoicedObject;

}

void AActorSafeRoad::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	DeleteObjects();

}
