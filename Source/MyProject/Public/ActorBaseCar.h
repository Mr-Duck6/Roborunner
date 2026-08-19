#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PawnPlayer.h"
#include "ActorBaseCar.generated.h"

class UStaticMeshComponent;
class USceneComponent;
class UBoxComponent;

class APawnPlayer;

DECLARE_LOG_CATEGORY_EXTERN(CarLog, Log, All);

UCLASS()
class MYPROJECT_API AActorBaseCar : public AActor
{
	GENERATED_BODY()

public:
	AActorBaseCar();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* CarMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trigger")
		UBoxComponent* TriggerBox;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	FVector CarMoveDirection;
	int32 CarSpeed;

	FVector StartLocation;
	UPROPERTY()
		float EndY;

	FVector CurrentCarLocation;
	FVector TargetCarLocation;


	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};