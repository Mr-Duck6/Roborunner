
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "PawnPlayer.generated.h"

class UStaticMeshComponent;
class USceneComponent;

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

	APawnPlayer();

protected:
	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Player status
	void SaveNewRecoed();
	void Death();
	void RecordInWPB();

	//Variable with progress bar
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float CurrentRecord;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxRecord;

private:
	//Movement
	void CeckTargetCell(int32 RoadNum, int32 CellNum);

	void MoveForward();
	void MoveBackward();
	void MoveLeft();
	void MoveRight();

	int32 TargetRoad;
	int32 TargetCell;

public:
	UPROPERTY(Visibleanywhere, BlueprintReadWrite)
	int32 PlayerRoadLocation;
	int32 PlayerCellLocation;

	bool CanMove;

protected:
	//World info
	UPROPERTY()
		class AActorGeneratorMap* CachedMapGenerator = nullptr;

private:
	const int32 OneStep = 100;
	const FVector NeededZCord = { 0,0,50 };


};