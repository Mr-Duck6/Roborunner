

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorCell.h"
#include "RoadTypes.h"
#include "ActorBaseRoad.generated.h"

UCLASS()
class MYPROJECT_API AActorBaseRoad : public AActor
{
	GENERATED_BODY()
	
public:	

	AActorBaseRoad();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class USceneComponent* Root;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class UStaticMeshComponent* BaseRoadMesh;

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		TSubclassOf<AActorCell> CellBP;
	const int32 RoadLenght = 11;
	TArray<AActorCell*> SpawnedCell;
	int32 CellStep;
	int32 StartSpawn;
	int32 EndSpawn;

	void GeneratCells();
	void DeleteCells();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Road Settings")
	ERoadType RoadType = ERoadType::BaseRoad;


};