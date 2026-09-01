
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

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	int32 MaxObjectsInRow = 3;

private:
	void SpawnObject();
	void DeleteObjects();
	int32 ChoiceObjectToSpawn();

	int32 ChoicedObject;
	int32 SpawnedObjectsCounter;


};