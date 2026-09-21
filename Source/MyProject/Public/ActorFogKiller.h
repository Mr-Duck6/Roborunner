
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorFogKiller.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(FogKillerLog, Log, All);

class APawnPlayer;
class UStaticMeshComponent;
class USceneComponent;
class UBoxComponent;

UCLASS()
class MYPROJECT_API AActorFogKiller : public AActor
{
	GENERATED_BODY()
	
public:	

	AActorFogKiller();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* FogMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trigger")
		UBoxComponent* TriggerBox;

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;


	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,
			bool bFromSweep,const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp,AActor* OtherActor,
			UPrimitiveComponent* OtherComp,int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TickLog")
		bool bVisibleTickLog;

	int32 CurrentSpeed;

	UPROPERTY()
		APawnPlayer* PlayerRef;

private: 

	const int32 MinSpeed = 150;
	const int32 MaxSpeed = 700;
	const int32 SpeedDefferences = 20;

	int32 OldDefference;

	void ChangeSpeed();

	FTimerHandle ChangeSpeedHandle;

};
