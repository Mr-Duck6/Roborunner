

#include "ActorTurret.h"
#include "PawnPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

DEFINE_LOG_CATEGORY(TurretLog);

AActorTurret::AActorTurret()
{
	PrimaryActorTick.bCanEverTick = false;

	TurretTraceDistance = 1100;

	SearchIntervalTime = 0.5f;

	PrepareTime = 4.f;

	ShootIntervalTime = 0.2f;
	ShootTime = 6.f;

	ReloadingTime = 3.f;

}

void AActorTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AActorTurret::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<APawnPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	SetTurrelState(ETurretState::Search);
}

void AActorTurret::SetTurrelState(ETurretState NewState)
{
	GetWorldTimerManager().ClearTimer(SearchTimerHandle);
	GetWorldTimerManager().ClearTimer(PrepareTimerHandle);
	GetWorldTimerManager().ClearTimer(ShootIntervalHandle);
	GetWorldTimerManager().ClearTimer(ShootTimerHandle);
	GetWorldTimerManager().ClearTimer(ReloadingTimerHandle);

	CurrentState = NewState;
	UE_LOG(TurretLog, Log, TEXT("Function SetTurretState called, new turret state %s"),*UEnum::GetValueAsString(CurrentState));

	switch (CurrentState)
	{
	case ETurretState::Search:

		GetWorldTimerManager().SetTimer(SearchTimerHandle,this, &AActorTurret::Search, SearchIntervalTime, true);

		break;

	case ETurretState::Prepare:

		GetWorldTimerManager().SetTimer(PrepareTimerHandle, this, &AActorTurret::PrepareForShoot, PrepareTime, false);

		break;

	case ETurretState::Shoot:

		GetWorldTimerManager().SetTimer(ShootIntervalHandle, this, &AActorTurret::Shoot, ShootIntervalTime, true);

		GetWorldTimerManager().SetTimer(ShootTimerHandle, this, &AActorTurret::Reloading, ShootTime, false);
		break;


	case ETurretState::Reloading:
		GetWorldTimerManager().SetTimer(ReloadingTimerHandle, this, &AActorTurret::RedyForSearch, ReloadingTime, false);
		break;

	default:
		GetWorldTimerManager().ClearTimer(SearchTimerHandle);
		GetWorldTimerManager().ClearTimer(PrepareTimerHandle);
		GetWorldTimerManager().ClearTimer(ShootIntervalHandle);
		GetWorldTimerManager().ClearTimer(ReloadingTimerHandle);
		SetTurrelState(ETurretState::Search);
		break;
	}
}

void AActorTurret::Search()
{
	//UE_LOG(TurretLog, Display, TEXT("Function Search called"));
	if (!IsValid(Player)) return;

	const int32 ZCordinate = 50;
	FVector Start = GetActorLocation() + FVector(0,0,ZCordinate);
	FVector End = Start + (FVector::RightVector * TurretTraceDistance);

	//DrawDebugLine(GetWorld(),Start,End,FColor::Green,false,1.f,0,2.f);

	TArray<FHitResult> HitResults;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceMultiByChannel(HitResults, Start, End, ECC_Visibility, CollisionParams);
	//UE_LOG(TurretLog, Log, TEXT("Hit - %s"), bHit ? TEXT("true") : TEXT("false"));
	if (bHit)
	{
		if (Player)
		{
			for (const FHitResult& HitResult : HitResults)
			{
				if (HitResult.GetActor() == Player)
				{
					UE_LOG(TurretLog, Display, TEXT("Search function: Player detected by trace"));
					SetTurrelState(ETurretState::Prepare);
					break;
				}
			}
		}
	}
}


void AActorTurret::PrepareForShoot()
{
	UE_LOG(TurretLog, Display, TEXT("Function PrepareForShoot called"));
	SetTurrelState(ETurretState::Shoot);
}

void AActorTurret::Shoot()
{
	UE_LOG(TurretLog, Display, TEXT("Function Shoot called"));
	if (!IsValid(Player)) return;

	const int32 ZCordinate = 50;
	FVector Start = GetActorLocation() + FVector(0, 0, ZCordinate);
	FVector End = Start + (FVector::RightVector * TurretTraceDistance);

	//DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.f, 0, 2.f);

	TArray<FHitResult> HitResults;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceMultiByChannel(HitResults, Start, End, ECC_Visibility, CollisionParams);
	UE_LOG(TurretLog, Log, TEXT("Hit - %s"), bHit ? TEXT("true") : TEXT("false"));
	if (bHit)
	{
		if (Player)
		{
			UE_LOG(TurretLog, Display, TEXT("Player found"));
			for (const FHitResult& HitResult : HitResults)
			{
				if (HitResult.GetActor() == Player)
				{
					UE_LOG(TurretLog, Display, TEXT("Player detected by trace"));
					Player->Death();
					break;
				}
			}
		}
	}
}

void AActorTurret::Reloading()
{
	UE_LOG(TurretLog, Display, TEXT("Function Reloading called"));

	SetTurrelState(ETurretState::Reloading);
}

void AActorTurret::RedyForSearch()
{
	GetWorldTimerManager().ClearTimer(ReloadingTimerHandle);
	SetTurrelState(ETurretState::Search);
}

void AActorTurret::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorldTimerManager().ClearTimer(SearchTimerHandle);
	GetWorldTimerManager().ClearTimer(PrepareTimerHandle);
	GetWorldTimerManager().ClearTimer(ShootIntervalHandle);
	GetWorldTimerManager().ClearTimer(ReloadingTimerHandle);

}

