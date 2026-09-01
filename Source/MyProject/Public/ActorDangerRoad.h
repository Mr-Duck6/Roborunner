

#pragma once

#include "CoreMinimal.h"
#include "ActorBaseRoad.h"
#include "ActorBaseCar.h"
#include "ActorDangerRoad.generated.h"

UENUM(BlueprintType)
enum class ERoadSpeedType : uint8
{
	Low,
	Medium,
	High
};

UCLASS()
class MYPROJECT_API AActorDangerRoad : public AActorBaseRoad
{
	GENERATED_BODY()

public:
	AActorDangerRoad();

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime) override;


	UPROPERTY(Editanywhere,BlueprintReadWrite,Category = "Car")
	TArray<TSubclassOf<AActorBaseCar>>AllBPCar;
	TArray<AActorBaseCar*> SpawnedCar;

	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Car")
	int32 LowSpeed = 200;
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Car")
	int32 MediumSpeed = 300;
	UPROPERTY(Editanywhere, BlueprintReadWrite, Category = "Car")
	int32 HighSpeed = 400;

	TArray<int32>CarPosition;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:

	FVector GetRandomDirection();
	int32 ChoiseRoadSpeed();
	int32 ChoiseCarToSpawn();
	int32 GetRandCarNums();

	void GetCarsPosition();
	void SpawnCar(int32 IndexPosition);
	void DeleteCar();

	int32 ChoisedCar;
	FVector RoadDirection;
	int32 RoadSpeed;
	int32 CarsOnRoad;

	FVector SpawnLocation;

};
