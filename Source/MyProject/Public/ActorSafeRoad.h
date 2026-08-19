
#pragma once

#include "CoreMinimal.h"
#include "ActorBaseRoad.h"
#include "ActorBaseObject.h"
#include "ActorSafeRoad.generated.h"

class USceneComponent;
class UStaticMeshComponent;

UCLASS()
class MYPROJECT_API AActorSafeRoad : public AActorBaseRoad
{
	GENERATED_BODY()

public:

	AActorSafeRoad();

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TArray<TSubclassOf<AActorBaseObject>> AllBPObject;

	TArray<AActorBaseObject*> SpawnedObjects;
	
	void SpawnObject();
	void DeleteObjects();
	int32 ChoiceObjectToSpawn();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	int32 ChoicedObject;
	const int32 MaxObjectsInRow = 3;
	int32 SpawnedObjectsCounter;

};