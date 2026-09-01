
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorCell.h"
#include "RoadTypes.h"
#include "ActorBaseObject.h"
#include "ActorBaseRoad.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(RoadLog, Log, All);

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

	void GeneratCells();
	void DeleteCells();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		TSubclassOf<AActorCell> CellBP;
	TArray<AActorCell*> SpawnedCell;

	int32 CellStep;
	int32 StartSpawn;
	int32 EndSpawn;

	void SpawnEdgeObjects();
	void DeleteEdgeObjects();
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<AActorBaseObject>EdgeObjectBP;
	TArray<AActorBaseObject*>SpawnedEdgeObjects;
	
	//Road parameters
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Road parametrs")
		int32 RoadID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Road parametrs")
		ERoadType RoadType = ERoadType::BaseRoad;
	const int32 RoadLenght = 11;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);


};