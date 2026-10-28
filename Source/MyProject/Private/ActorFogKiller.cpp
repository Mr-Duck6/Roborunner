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

	CurrentSpeed = BaseSpeed;
}

void AActorFogKiller::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AActorFogKiller::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AActorFogKiller::OnOverlapEnd);

	PlayerRef = Cast<APawnPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (!IsValid(PlayerRef))
	{
		UE_LOG(FogKillerLog, Display, TEXT("Player for fog not found"));
		return;
	}
}

void AActorFogKiller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	ChangeFogSpeed();

	FVector CurrentLocation = GetActorLocation();
	FVector TargetLocation = CurrentLocation + FVector(CurrentSpeed * DeltaTime, 0.0f, 0.0f);
	SetActorLocation(TargetLocation);


}


void AActorFogKiller::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValid(PlayerRef))
	{
		UE_LOG(FogKillerLog, Error, TEXT("Player not found"));
		return;
	}

	if (OtherActor && (OtherActor != this) && (OtherActor == PlayerRef))
	{
		UE_LOG(FogKillerLog, Display, TEXT("Fog kill the player"));
		PlayerRef->Death();
	}
}

void AActorFogKiller::OnOverlapEnd(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AActorFogKiller::ChangeFogSpeed()
{
	if (!IsValid(PlayerRef))
	{
		UE_LOG(FogKillerLog, Display, TEXT("Player for fog not found"));
		return;
	}

	float PlayerLoc = PlayerRef->PlayerRoadLocation;
	float FogLoc = GetActorLocation().X;

	float DistanceBetween = PlayerLoc * 100 - FogLoc;

	CurrentSpeed = BaseSpeed;
	float LastSpeed;

	if (DistanceBetween >= 3000)
	{
		CurrentSpeed = MaxSpeed;
		LastSpeed = MaxSpeed;
	}
	else if(DistanceBetween >= 1500)
	{
		CurrentSpeed = MiddleSpeed;
		LastSpeed = MiddleSpeed;
	}
	else
	{
		CurrentSpeed = BaseSpeed;
		LastSpeed = BaseSpeed;
	}

	//Speed log
	if (CurrentSpeed != LastSpeed)
	{
		UE_LOG(FogKillerLog, Log, TEXT("New Fog speed is: %f"), CurrentSpeed);
	}

	//UE_LOG(FogKillerLog, Log, TEXT("Fog speed: %f,Player Road location: %f, Fog location %f, DistanceBetween: %f"), CurrentSpeed,PlayerLoc,FogLoc, DistanceBetween);
}