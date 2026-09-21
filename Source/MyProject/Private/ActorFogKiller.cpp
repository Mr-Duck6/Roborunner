
#include "ActorFogKiller.h"
#include "PawnPlayer.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(FogKillerLog);

AActorFogKiller::AActorFogKiller()
{

	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(Root);

	FogMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FogMesh"));
	FogMesh->SetupAttachment(Root);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(FogMesh);

	CurrentSpeed = 160;
	OldDefference = -1;

	bVisibleTickLog = false;

}


void AActorFogKiller::BeginPlay()
{
	Super::BeginPlay();
	
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AActorFogKiller::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AActorFogKiller::OnOverlapEnd);

	PlayerRef = Cast<APawnPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));

	GetWorldTimerManager().SetTimer(ChangeSpeedHandle, this, &AActorFogKiller::ChangeSpeed, 1.f, true, 1.f);

}


void AActorFogKiller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bVisibleTickLog)//Logs
	{
		UE_LOG(FogKillerLog, Log, TEXT("Current fog position %s"), *GetActorLocation().ToString());
		UE_LOG(FogKillerLog, Log, TEXT("Current fog speed %i"), CurrentSpeed);
	}

	FVector CurrentFogLocation = GetActorLocation();
	FVector TargetLocation = CurrentFogLocation + FVector(CurrentSpeed, 0, 0) * DeltaTime;
	SetActorLocation(TargetLocation);

}



void AActorFogKiller::ChangeSpeed()
{
	if (!IsValid(PlayerRef))
	{
		UE_LOG(FogKillerLog, Error, TEXT("Player is invalid"));
		return;
	}

	int32 FogCurrentLocation = GetActorLocation().X;
	int32 PlayerCurrentLocation = PlayerRef->PlayerRoadLocation;
	int32 DistenceDifference = FMath::Abs(FogCurrentLocation - PlayerCurrentLocation);

	if (bVisibleTickLog)//Logs
	{
		UE_LOG(FogKillerLog, Log, TEXT("Current fog location is: %i, Player current location: %i"),
			FogCurrentLocation, PlayerCurrentLocation);
		UE_LOG(FogKillerLog, Log, TEXT("Distance difference is: %i, Old difference: %i"),
			DistenceDifference, OldDefference);
	}

	//First tick
	if (OldDefference < 0)
	{
		OldDefference = DistenceDifference;
		return; 
	}

	if (DistenceDifference < OldDefference)
	{
		CurrentSpeed -= SpeedDefferences;
	}
	else if (DistenceDifference > OldDefference)
	{
		CurrentSpeed += SpeedDefferences;
	}

	OldDefference = DistenceDifference;
	CurrentSpeed = FMath::Clamp(CurrentSpeed, MinSpeed, MaxSpeed);

	if (bVisibleTickLog)//Logs
	{
		UE_LOG(FogKillerLog, Log, TEXT("Distance difference is: %i, Old difference: %i"),
			DistenceDifference, OldDefference);
	}

}

//Kill player
void AActorFogKiller::OnOverlapBegin(UPrimitiveComponent* OverlappedComp,AActor* OtherActor,
	UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult)
{
	if(!IsValid(PlayerRef))
	{
		UE_LOG(FogKillerLog, Error, TEXT("Player not found"));
		return;
	}

	if (OtherActor && (OtherActor != this))
	{
		if (OtherActor == PlayerRef)
		{
			UE_LOG(FogKillerLog, Display, TEXT("Fog kill the player"));
			PlayerRef->Death();
		}
	}
}

void AActorFogKiller::OnOverlapEnd(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex)
{
	//UE_LOG(FogKillerLog, Display, TEXT("Player outside the fog"));
}