
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

	float CurrentSpeed;

	UPROPERTY()
		APawnPlayer* PlayerRef;

private:
	float BaseSpeed = 80;
	const float MiddleSpeed = 150;
	const float MaxSpeed = 300;

	void ChangeFogSpeed();

};
