

#include "PawnPlayer.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"
#include "ActorGeneratorMap.h"
#include "Kismet/GameplayStatics.h"
#include "MySaveGame.h"
#include "MyGameInstance.h"
#include "GameFramework/SpringArmComponent.h"

DEFINE_LOG_CATEGORY(PlayerLog);

APawnPlayer::APawnPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerRoadLocation = 0;
	PlayerCellLocation = 5;
	CanMove = true;

	CurrentRecord = PlayerRoadLocation;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(Root);

	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));

	PlayerMesh->SetupAttachment(Root);

}

void APawnPlayer::BeginPlay()
{
	Super::BeginPlay();

	//Get generator map
	CachedMapGenerator = Cast<AActorGeneratorMap>(UGameplayStatics::GetActorOfClass(GetWorld(), AActorGeneratorMap::StaticClass()));
	if (!CachedMapGenerator)
	{
		UE_LOG(PlayerLog, Error, TEXT("CachedMapGenerator not found"));
		return;
	}
	//Check base spawned objects
	if (CachedMapGenerator->SpawnedRoad.IsValidIndex(0) &&
		CachedMapGenerator->SpawnedRoad[0] &&
		CachedMapGenerator->SpawnedRoad[0]->SpawnedCell.IsValidIndex(6))
	{
		auto CurrentCell = CachedMapGenerator->SpawnedRoad[0]->SpawnedCell[6];
		if (CurrentCell)
		{
			//Set start position
			FVector StartLocation = CurrentCell->CellCenterLocation + FVector(0,0,50);
			SetActorLocation(StartLocation);
		}
	}
	else
	{
		UE_LOG(PlayerLog, Warning, TEXT("The map has not yet been generated."));
	}

	//Get game instance for getting max record
	UMyGameInstance* GI = Cast<UMyGameInstance>(GetGameInstance());
	if (GI && GI->CurrentSave)
	{
		MaxRecord = GI->CurrentSave->PlayerRecord;
	}
}

void APawnPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APawnPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("MoveForward",IE_Pressed,this,&APawnPlayer::MoveForward);
	PlayerInputComponent->BindAction("MoveBackward", IE_Pressed, this, &APawnPlayer::MoveBackward);
	PlayerInputComponent->BindAction("MoveLeft", IE_Pressed, this, &APawnPlayer::MoveLeft);
	PlayerInputComponent->BindAction("MoveRight", IE_Pressed, this, &APawnPlayer::MoveRight);

}

void APawnPlayer::CeckTargetCell(int32 RoadNum, int32 CellNum)
{
	CanMove = false;

	if (!IsValid(CachedMapGenerator) || RoadNum < 0 || CellNum < 0) return;

	AActorBaseRoad* TargetRoadActor = CachedMapGenerator->GetRoadByID(RoadNum);

	if (IsValid(TargetRoadActor) && TargetRoadActor->SpawnedCell.IsValidIndex(CellNum))
	{
		auto CurrentCell = TargetRoadActor->SpawnedCell[CellNum];
		if (IsValid(CurrentCell))
		{
			CanMove = !CurrentCell->Occupied;
		}
	}
}

void APawnPlayer::MoveForward()
{
	UE_LOG(PlayerLog, Display, TEXT("Function MoveForward called"));

	CanMove = false;
	TargetRoad = PlayerRoadLocation + 1;

	CeckTargetCell(TargetRoad, PlayerCellLocation);

	UE_LOG(PlayerLog, Log, TEXT("CanMove is: %s"), CanMove ? TEXT("true") : TEXT("false"));
	if (CanMove)
	{

		if (IsValid(CachedMapGenerator))
		{
			AActorBaseRoad* TargetActorRoad = CachedMapGenerator->GetRoadByID(TargetRoad);

			if (IsValid(TargetActorRoad) && TargetActorRoad->SpawnedCell.IsValidIndex(PlayerCellLocation))
			{
				auto TargetCellObj = TargetActorRoad->SpawnedCell[PlayerCellLocation];
				if (IsValid(TargetCellObj))
				{
					RecordInWPB();

					PlayerRoadLocation = TargetRoad;
					FVector NewLocation = TargetCellObj->CellCenterLocation + NeededZCord;
					SetActorLocation(NewLocation);
				}
			}
		}
	}
}

void APawnPlayer::MoveBackward()
{
	UE_LOG(PlayerLog, Display, TEXT("Function MoveBackward called"));

	CanMove = false;
	TargetRoad = PlayerRoadLocation - 1;

	CeckTargetCell(TargetRoad, PlayerCellLocation);

	UE_LOG(PlayerLog, Log, TEXT("CanMove is: %s"), CanMove ? TEXT("true") : TEXT("false"));
	if (CanMove)
	{

		if (IsValid(CachedMapGenerator))
		{
			AActorBaseRoad* TargetActorRoad = CachedMapGenerator->GetRoadByID(TargetRoad);

			if (IsValid(TargetActorRoad) && TargetActorRoad->SpawnedCell.IsValidIndex(PlayerCellLocation))
			{
				auto TargetCellObj = TargetActorRoad->SpawnedCell[PlayerCellLocation];
				if (IsValid(TargetCellObj))
				{
					PlayerRoadLocation = TargetRoad;
					FVector NewLocation = TargetCellObj->CellCenterLocation + NeededZCord;
					SetActorLocation(NewLocation);
				}
			}
		}
	}
}

void APawnPlayer::MoveLeft()
{
	CanMove = false;

	UE_LOG(PlayerLog, Display, TEXT("Function MoveLeft called"));
	TargetCell = PlayerCellLocation - 1;

	CeckTargetCell(PlayerRoadLocation, TargetCell);

	UE_LOG(PlayerLog, Log, TEXT("CanMove is: %s"), CanMove ? TEXT("true") : TEXT("false"));
	if (CanMove)
	{

		if (IsValid(CachedMapGenerator))
		{
			AActorBaseRoad* CurrentRoadActor = CachedMapGenerator->GetRoadByID(PlayerRoadLocation);

			if (IsValid(CurrentRoadActor) && CurrentRoadActor->SpawnedCell.IsValidIndex(TargetCell))
			{
				auto TargetCellObj = CurrentRoadActor->SpawnedCell[TargetCell];
				if (IsValid(TargetCellObj))
				{
					UE_LOG(PlayerLog, Display, TEXT("Player move left"));
					PlayerCellLocation = TargetCell;

					FVector NewLocation = TargetCellObj->CellCenterLocation + NeededZCord;
					UE_LOG(PlayerLog, Display, TEXT("Player new location is: %s"), *NewLocation.ToString());
					SetActorLocation(NewLocation);
				}
			}
		}
	}
}

void APawnPlayer::MoveRight()
{
	CanMove = false;

	UE_LOG(PlayerLog, Display, TEXT("Function MoveRight called"));
	TargetCell = PlayerCellLocation + 1;

	CeckTargetCell(PlayerRoadLocation, TargetCell);

	UE_LOG(PlayerLog, Log, TEXT("CanMove is: %s"), CanMove ? TEXT("true") : TEXT("false"));
	if (CanMove)
	{
		if (IsValid(CachedMapGenerator))
		{
			AActorBaseRoad* CurrentRoadActor = CachedMapGenerator->GetRoadByID(PlayerRoadLocation);

			if (IsValid(CurrentRoadActor) && CurrentRoadActor->SpawnedCell.IsValidIndex(TargetCell))
			{
				auto TargetCellObj = CurrentRoadActor->SpawnedCell[TargetCell];
				if (IsValid(TargetCellObj))
				{
					UE_LOG(PlayerLog, Display, TEXT("Player move right"));
					PlayerCellLocation = TargetCell;

					FVector NewLocation = TargetCellObj->CellCenterLocation + NeededZCord;
					UE_LOG(PlayerLog, Display, TEXT("Player new location is: %s"), *NewLocation.ToString());
					SetActorLocation(NewLocation);
				}
			}
		}
	}
}

void APawnPlayer::SaveNewRecoed()//Save current player road location if this move the oldest record
{
	UMyGameInstance* GI = Cast<UMyGameInstance>(GetGameInstance());

	if (GI && GI->CurrentSave)
	{
		int32 Record = GI->CurrentSave->PlayerRecord;

		if (PlayerRoadLocation > Record)
		{
			GI->SaveGame(PlayerRoadLocation);
		}
	}
}

void APawnPlayer::Death()
{
	UE_LOG(PlayerLog, Display, TEXT("Death function called"));

	SaveNewRecoed();

	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(GetGameInstance());

	if (GameInstance)
	{
		GameInstance->ReturnPlayerToMenu();
	}
}

void APawnPlayer::RecordInWPB()
{
	UE_LOG(PlayerLog, Display, TEXT("Function RecordInWPB called"));
	CurrentRecord = FMath::Clamp(CurrentRecord, 0.f, MaxRecord);

	if (PlayerRoadLocation < CurrentRecord)
	{
		UE_LOG(PlayerLog, Display, TEXT("PlayerRoadLocation less than CurrentRecord"));
		return;
	}
	else
	{
		UE_LOG(PlayerLog, Log, TEXT("New CurrentRecord is: %f"), CurrentRecord);
		CurrentRecord = PlayerRoadLocation;
	}
}