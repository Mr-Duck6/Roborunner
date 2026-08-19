
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


	//Road
	void SpawnRoad();
	void DeleteRoad();
	int32 ChoiceRoadToSpawn();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
		TArray<TSubclassOf<AActorBaseRoad>> AllBPRoads;
	TSoftClassPtr<AActorBaseRoad> BaseRoad;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
		TArray<AActorBaseRoad*> SpawnedRoad;

	UPROPERTY(EditAnywhere, Category = "Map Generation")
		int32 StartSpawnThreshold = 15;

	int32 ChoicedRoad;
	const int32 InitialQuantityRoad = 30;
	FVector SpawnRoadLocation;

	int32 SafeRoadCounter;
	int32 DangerRoadCounter;
	int32 TurrelRoadCounter;

	const int32 MaxSafeRoadInRow = 3;
	const int32 MaxDangerRoadInRow = 4;
	const int32 MaxTurrelRoadInRow = 2;

	//Spawn new road
	AActorBaseRoad* GetRoadByID(int32 TargetID);
	int32 NextRoadID;
	int32 NextTriggerLocation = 15;
	int32 CurrentPlayerLocation;
};