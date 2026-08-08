

#include "PawnPlayer.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"
#include "ActorGeneratorMap.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"

DEFINE_LOG_CATEGORY(PlayerLog);


APawnPlayer::APawnPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerRoadLocation = 0;
	PlayerCellLocation = 6;
	CanMove = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(Root);

	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	PlayerSpingArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("PlayerSpringArm"));
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));

	PlayerMesh->SetupAttachment(Root);
	PlayerSpingArm->SetupAttachment(Root);
	PlayerCamera->SetupAttachment(PlayerSpingArm);

}

void APawnPlayer::BeginPlay()
{
	Super::BeginPlay();

	AActorGeneratorMap* Map = Cast<AActorGeneratorMap>(UGameplayStatics::GetActorOfClass(GetWorld(), AActorGeneratorMap::StaticClass()));

	if (IsValid(Map))
	{
		Map->SpawnedRoad[0]->SpawnedCell[6]->CellCenterLocation;
		FVector StartLocation;
		SetActorLocation(StartLocation);
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

void APawnPlayer::CheckCollision(FVector MoveDirection)
{

	FVector Start = GetActorLocation();
	FVector End = Start + MoveDirection;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	FHitResult HitInfo;

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitInfo, Start, End, ECC_Visibility, CollisionParams);

	if (!bHit)
	{
		CanMove = true;
	}
	else
	{
		CanMove = false;
	}

}

void APawnPlayer::CeckTargetCell(int32 RoadNum, int32 CellNum)
{
	AActorGeneratorMap* Map = Cast<AActorGeneratorMap>(UGameplayStatics::GetActorOfClass(GetWorld(), AActorGeneratorMap::StaticClass()));

	if (RoadNum < 0 || CellNum < 0)
	{
		UE_LOG(PlayerLog,Log,TEXT("RoadNum is: %i, CellNum is: %i. Function has been returned"), RoadNum,CellNum);
		return;
	}

	if (Map->SpawnedRoad.IsValidIndex(RoadNum))
	{
		auto CurrentRoad = Map->SpawnedRoad[RoadNum];

		if (CurrentRoad != nullptr)
		{
			if (CurrentRoad->SpawnedCell.IsValidIndex(CellNum))
			{
				auto CurrentCell = CurrentRoad->SpawnedCell[CellNum];

				if (CurrentCell != nullptr)
				{
					bool IsFreeCell = Map->SpawnedRoad[RoadNum]->SpawnedCell[CellNum]->Occupied;

					if (!IsFreeCell)
					{
						CanMove = true;
					}
				}
			}
		}
	}

}

void APawnPlayer::MoveForward()
{
	UE_LOG(PlayerLog, Display, TEXT("Function MoveForward called"));
	FVector Direction(0, 100, 0);
	TargetRoad = PlayerRoadLocation + 1;

	CheckCollision(Direction);
	CeckTargetCell(TargetRoad, PlayerCellLocation);

	UE_LOG(PlayerLog, Log, TEXT("CanMove is: %s"), CanMove ? TEXT("true") : TEXT("false"));
	if (CanMove)
	{
		AActorGeneratorMap* Map = Cast<AActorGeneratorMap>(UGameplayStatics::GetActorOfClass(GetWorld(), AActorGeneratorMap::StaticClass()));

		if (IsValid(Map))
		{
			PlayerRoadLocation = TargetRoad;
			FVector NewLocation = Map->SpawnedRoad[TargetRoad]->SpawnedCell[PlayerCellLocation]->CellCenterLocation + NeededZCord;
			UE_LOG(PlayerLog, Display, TEXT("Player move forward \n New location is: %s"), *NewLocation.ToString());
			SetActorLocation(NewLocation);
		}
	}
}

void APawnPlayer::MoveBackward()
{
	UE_LOG(PlayerLog, Display, TEXT("Function MoveBackward called"));
	FVector Direction(0, -100, 0);
	TargetRoad = PlayerRoadLocation - 1;

	CheckCollision(Direction);
	CeckTargetCell(TargetRoad, PlayerCellLocation);

	UE_LOG(PlayerLog, Log, TEXT("CanMove is: %s"), CanMove ? TEXT("true") : TEXT("false"));
	if (CanMove)
	{
		AActorGeneratorMap* Map = Cast<AActorGeneratorMap>(UGameplayStatics::GetActorOfClass(GetWorld(), AActorGeneratorMap::StaticClass()));

		if (IsValid(Map))
		{
			UE_LOG(PlayerLog, Display, TEXT("Player move backward"));
			PlayerRoadLocation = TargetRoad;
			FVector NewLocation = Map->SpawnedRoad[TargetRoad]->SpawnedCell[PlayerCellLocation]->CellCenterLocation + NeededZCord;
			UE_LOG(PlayerLog, Display, TEXT("Player move forward \n New location is: %s"), *NewLocation.ToString());
			SetActorLocation(NewLocation);
		}
	}
}

void APawnPlayer::MoveLeft()
{
	UE_LOG(PlayerLog, Display, TEXT("Function MoveLeft called"));
	FVector Direction(-100, 0, 0);
	TargetCell = PlayerCellLocation - 1;

	CheckCollision(Direction);
	CeckTargetCell(PlayerRoadLocation, TargetCell);

	UE_LOG(PlayerLog, Log, TEXT("CanMove is: %s"), CanMove ? TEXT("true") : TEXT("false"));
	if (CanMove)
	{
		AActorGeneratorMap* Map = Cast<AActorGeneratorMap>(UGameplayStatics::GetActorOfClass(GetWorld(), AActorGeneratorMap::StaticClass()));

		if (IsValid(Map))
		{
			UE_LOG(PlayerLog, Display, TEXT("Player move left"));
			PlayerCellLocation = TargetCell;
			FVector NewLocation = Map->SpawnedRoad[PlayerRoadLocation]->SpawnedCell[TargetCell]->CellCenterLocation + NeededZCord;
			UE_LOG(PlayerLog, Display, TEXT("Player move forward \n New location is: %s"), *NewLocation.ToString());
			SetActorLocation(NewLocation);
		}
	}
}

void APawnPlayer::MoveRight()
{
	UE_LOG(PlayerLog, Display, TEXT("Function MoveRight called"));
	FVector Direction(100, 0, 0);
	TargetCell = PlayerCellLocation + 1;

	CheckCollision(Direction);
	CeckTargetCell(PlayerRoadLocation, TargetCell);

	UE_LOG(PlayerLog, Log, TEXT("CanMove is: %s"), CanMove ? TEXT("true") : TEXT("false"));
	if (CanMove)
	{
		AActorGeneratorMap* Map = Cast<AActorGeneratorMap>(UGameplayStatics::GetActorOfClass(GetWorld(), AActorGeneratorMap::StaticClass()));

		if (IsValid(Map))
		{
			UE_LOG(PlayerLog, Display, TEXT("Player move right"));
			PlayerCellLocation = TargetCell;
			FVector NewLocation = Map->SpawnedRoad[PlayerRoadLocation]->SpawnedCell[TargetCell]->CellCenterLocation + NeededZCord;
			UE_LOG(PlayerLog, Display, TEXT("Player move forward \n New location is: %s"), *NewLocation.ToString());
			SetActorLocation(NewLocation);
		}
	}
} 