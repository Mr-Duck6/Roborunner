#include "ActorBaseCar.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "PawnPlayer.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(CarLog);

AActorBaseCar::AActorBaseCar()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(Root);

	CarMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CarMesh"));
	CarMesh->SetupAttachment(Root);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(CarMesh);

	CarSpeed = 200;
}

void AActorBaseCar::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AActorBaseCar::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AActorBaseCar::OnOverlapEnd);

}

void AActorBaseCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();//Move car
	NewLocation += CarMoveDirection * CarSpeed * DeltaTime;

	bool bReachedEnd = false;

	if (CarMoveDirection == FVector::RightVector)//Check end car position
	{
		bReachedEnd = NewLocation.Y >= EndY;
	}
	else
	{
		bReachedEnd = NewLocation.Y <= EndY;
	}

	if (bReachedEnd)//Teleport car to start location
	{
		NewLocation = StartLocation;
	}

	SetActorLocation(NewLocation);
	
}

void AActorBaseCar::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor && (OtherActor != this))
	{
		APawnPlayer* Player = Cast<APawnPlayer>((UGameplayStatics::GetActorOfClass(GetWorld(), APawnPlayer::StaticClass())));
		if (Player && OtherActor == Player)
		{
			UE_LOG(CarLog, Display, TEXT("Trigger on"));
			Player->Death();
		}
	}

}

void AActorBaseCar::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this))
	{
		//UE_LOG(CarLog, Display, TEXT("Trigger out"));
		return;
	}
}