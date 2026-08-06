

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorBaseRoad.h"
#include "PawnPlayer.h"
#include "ActorGeneratorMap.generated.h"

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

	void PlayerProgression();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
		TArray<TSubclassOf<AActorBaseRoad>> AllBPRoads;
	TSoftClassPtr<AActorBaseRoad> BaseRoad;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
		TArray<AActorBaseRoad*> SpawnedRoad;

	int32 SafeRoadCounter;
	int32 DangerRoadCounter;
	int32 TurrelRoadCounter;

	int32 ChoicedRoad;
	bool CanBeDeleted;
};