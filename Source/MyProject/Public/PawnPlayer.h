
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PawnPlayer.generated.h"

class UStaticMeshComponent;
class USceneComponent;
class UCameraComponent;
class USpringArmComponent;

DECLARE_LOG_CATEGORY_EXTERN(PlayerLog, Log, All);


UCLASS()
class MYPROJECT_API APawnPlayer : public APawn
{
	GENERATED_BODY()

public:

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* PlayerMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		USpringArmComponent* PlayerSpingArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UCameraComponent* PlayerCamera;

	APawnPlayer();

protected:
	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void CeckTargetCell(int32 RoadNum, int32 CellNum);

	//Movement function
	void MoveForward();
	void MoveBackward();
	void MoveLeft();
	void MoveRight();

	//Player location
	UPROPERTY(Visibleanywhere, BlueprintReadWrite)
	int32 PlayerRoadLocation;
	int32 PlayerCellLocation;

	int32 TargetRoad;
	int32 TargetCell;

	const int32 OneStep = 100;
	const FVector NeededZCord = {0,0,50};
	bool CanMove;

protected:

	UPROPERTY()
		class AActorGeneratorMap* CachedMapGenerator = nullptr;

public:
	//Update player status

	void PlayerRecordUpdate();
	void Death();
};