#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorPlayerCamera.generated.h"

class USceneComponent;
class UCameraComponent;
class USpringArmComponent;
class APawnPlayer;

UCLASS()
class MYPROJECT_API AActorPlayerCamera : public AActor
{
	GENERATED_BODY()

public:
	AActorPlayerCamera();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		USpringArmComponent* SpringArm;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings")
		float YLeftLimit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings")
		float YRightLimit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings")
		float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera Settings")
		APawnPlayer* PlayerRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Settings")
		FVector DistanceBetweenPlayer;
};