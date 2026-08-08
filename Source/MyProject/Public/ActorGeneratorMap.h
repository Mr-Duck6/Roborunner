

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

	void SpawnRoad();
	void DeleteRoad();
	int32 ChoiceRoadToSpawn();

	void SpawnFence(FVector SpawnLocation);
	void DeleteFence();

	void PlayerProgression();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
		TArray<TSubclassOf<AActorBaseRoad>> AllBPRoads;
	TSoftClassPtr<AActorBaseRoad> BaseRoad;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
		TArray<AActorBaseRoad*> SpawnedRoad;

	TArray<AActorBaseObject*> SpawnedFence;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
		TSubclassOf<AActorBaseObject> TallFence;

	int32 SafeRoadCounter;
	int32 DangerRoadCounter;
	int32 TurrelRoadCounter;

	int32 ChoicedRoad;
	bool CanBeDeleted;
	const int32 InitialQuantityRoad = 30;
	FVector SpawnRoadLocation;

	FVector DistanceBetweenFence;

};