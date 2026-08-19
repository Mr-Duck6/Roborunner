
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
    int32 LocalSpawnedCounter = 0;

    for (int32 i = 0; i < SpawnedCell.Num(); i++)
    {
        if (LocalSpawnedCounter >= MaxObjectsInRow)//Limit
        {
            return;
        }

        bool bCreateObject = FMath::RandBool();

        if (bCreateObject && IsValid(SpawnedCell[i]))//Spawn random object in random cell
        {
            int32 SelectedIndex = ChoiceObjectToSpawn();

            if (AllBPObject.IsValidIndex(SelectedIndex) && AllBPObject[SelectedIndex])
            {
                FVector SpawnLocation = SpawnedCell[i]->CellCenterLocation;
                FRotator SpawnRotation = FRotator::ZeroRotator;

                AActorBaseObject* NewObject = GetWorld()->SpawnActor<AActorBaseObject>(
                    AllBPObject[SelectedIndex], SpawnLocation, SpawnRotation);

                if (NewObject)
                {
                    SpawnedObjects.Add(NewObject);
                    SpawnedCell[i]->Occupied = true;
                    LocalSpawnedCounter++;
                }
            }
        }
    }
}

void AActorSafeRoad::DeleteObjects()
{
    for (AActorBaseObject* Obj : SpawnedObjects)
    {
        if (IsValid(Obj))
        {
            UE_LOG(RoadLog, Log, TEXT("Delete object: %s"), *Obj->GetName());
            Obj->Destroy();
        }
    }

    SpawnedObjects.Empty();
}

int32 AActorSafeRoad::ChoiceObjectToSpawn()//Choise object to spawn
{
    if (AllBPObject.Num() == 0)
    {
        return INDEX_NONE;
    }

	ChoicedObject = FMath::RandRange(0, AllBPObject.Num() - 1);
	UE_LOG(RoadLog, Log, TEXT("Choice object: %s"), *AllBPObject[ChoicedObject]->GetName());
	return ChoicedObject;

}

void AActorSafeRoad::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	DeleteObjects();

}
