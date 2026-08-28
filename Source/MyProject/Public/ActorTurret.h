
#pragma once

#include "CoreMinimal.h"
#include "ActorBaseObject.h"
#include "ActorTurret.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(TurretLog, Log, All);

UENUM(BlueprintType)
enum class ETurretState : uint8
{
	Search,
	Prepare,
	Shoot,
	Reloading
};


UCLASS()
class MYPROJECT_API AActorTurret : public AActorBaseObject
{
	GENERATED_BODY()

public:

	AActorTurret();

protected:

	virtual void Tick(float DeltaTime) override;

public:

	virtual void BeginPlay()override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;

	UPROPERTY()
	ETurretState CurrentState;
	void SetTurrelState(ETurretState NewState);

	UPROPERTY()
		class APawnPlayer* Player;


	//Search
	void Search();
	FTimerHandle SearchTimerHandle;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		float SearchIntervalTime;

	//Prepare
	void PrepareForShoot();
	FTimerHandle PrepareTimerHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float PrepareTime;

	//Shoot
	void Shoot();
	FTimerHandle ShootIntervalHandle;
	float ShootIntervalTime;
	FTimerHandle ShootTimerHandle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ShootTime;

	//Reloading
	void Reloading();
	FTimerHandle ReloadingTimerHandle;
	float ReloadingTime;

	void RedyForSearch();


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 TurretTraceDistance;
};
