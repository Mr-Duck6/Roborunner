

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorBaseRoad.h"
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
	void ChoiseRoadToSpawn();

	void PlayerProgression();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<TSoftClassPtr<AActorBaseRoad>> AllBPRoad;
	TArray<AActorBaseRoad*> SpawnedRoad;


};
