
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorBaseRoad.h"
#include "PawnPlayer.h"
#include "ActorBaseObject.h"
#include "ActorGeneratorMap.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(GeneratorMapLog, Log, All);


UCLASS()
class MYPROJECT_API AActorGeneratorMap : public AActor
{
	GENERATED_BODY()
	
public:	

	AActorGeneratorMap();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;
	void PlayerProgression();

	void SpawnRoad();
	void DeleteRoad();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
		TArray<TSubclassOf<AActorBaseRoad>> AllBPRoads;
	TSoftClassPtr<AActorBaseRoad> BaseRoad;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
		TArray<AActorBaseRoad*> SpawnedRoad;

	UPROPERTY(EditAnywhere, Category = "Map Generation")
		int32 StartSpawnThreshold = 15;

	//Limits
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	 int32 MaxSafeRoadInRow = 3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	 int32 MaxDangerRoadInRow = 4;

	AActorBaseRoad* GetRoadByID(int32 TargetID);
	int32 NextRoadID;
	int32 NextTriggerLocation = 15;
	int32 CurrentPlayerLocation;

	//First road
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
		TSubclassOf<AActorBaseRoad> FirstRoadBP;

private:
	int32 ChoiceRoadToSpawn();
	int32 ChoicedRoad;
	const int32 InitialQuantityRoad = 30;
	FVector SpawnRoadLocation;

	//Counters
	int32 SafeRoadCounter;
	int32 DangerRoadCounter;

	//First road
	int32 FirstRoadsCounter;
	const int32 FirstRoads = 5;
	void SpawnFirstRoad();

	const FVector StepToSpawn = { 100, 0, 0 };


};