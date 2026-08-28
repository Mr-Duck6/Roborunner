

#pragma once

#include "CoreMinimal.h"
#include "ActorBaseRoad.h"
#include "ActorTurretRoad.generated.h"

class AActorTurret;

UCLASS()
class MYPROJECT_API AActorTurretRoad : public AActorBaseRoad
{
	GENERATED_BODY()

public:

	AActorTurretRoad();

protected:
	
	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaTime);

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);
	
	AActorTurret* Turret;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf <AActorTurret> TurretBP;

	void SpawnTurret();
	void DeleteTurret();

};
