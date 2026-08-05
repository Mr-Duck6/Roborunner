

#include "PawnPlayer.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

APawnPlayer::APawnPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerRoadLocation = 0;
	PlayerCellLocation = 6;
	CanMove = false;

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
	
}

void APawnPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APawnPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APawnPlayer::CheckCollision(FVector MoveDirection)
{
	FVector Start = GetActorLocation();
	FVector End = GetActorLocation() + MoveDirection;
	FCollisionQueryParams ColisionParams;
	ColisionParams.AddIgnoredActor(this);
	FHitResult HitInfo;

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitInfo, Start, End, ECC_Visibility, ColisionParams);

	if (bHit)
	{
		CanMove = true;
	}

}

void APawnPlayer::CeckTargetCell(int32 RoadNum, int32 CellNum)
{

}

void APawnPlayer::MoveForward()
{

	FVector Direction(0, 100, 0);
	TargetRoad = PlayerRoadLocation + 1;

	CheckCollision(Direction);
	CeckTargetCell(TargetRoad, PlayerCellLocation);

	if (CanMove)
	{
		PlayerRoadLocation = TargetRoad;
	}
}

void APawnPlayer::Backward()
{
	FVector Direction(0, -100, 0);
	TargetRoad = PlayerRoadLocation - 1;

	CheckCollision(Direction);
	CeckTargetCell(TargetRoad, PlayerCellLocation);

	if (CanMove)
	{
		PlayerRoadLocation = TargetRoad;
	}
}

void APawnPlayer::MoveLeft()
{
	FVector Direction(-100, 0, 0);
	TargetCell = PlayerCellLocation - 1;

	CheckCollision(Direction);
	CeckTargetCell(PlayerRoadLocation, TargetCell);

	if (CanMove)
	{
		PlayerCellLocation = TargetCell;
	}
}

void APawnPlayer::MoveRight()
{
	FVector Direction(100, 0, 0);
	TargetCell = PlayerCellLocation + 1;

	CheckCollision(Direction);
	CeckTargetCell(PlayerRoadLocation, TargetCell);

	if (CanMove)
	{
		PlayerCellLocation = TargetCell;
	}
}

