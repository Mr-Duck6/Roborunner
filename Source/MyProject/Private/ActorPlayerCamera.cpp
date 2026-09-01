#include "ActorPlayerCamera.h"
#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PawnPlayer.h"
#include "Kismet/GameplayStatics.h"

AActorPlayerCamera::AActorPlayerCamera()
{
	PrimaryActorTick.bCanEverTick = true;

	// Components
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(SceneComponent);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(SceneComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	// Variables initialization
	YLeftLimit = -500.f;
	YRightLimit = 500.f;
	Speed = 5.0f;

	DistanceBetweenPlayer = FVector(-300.0f, 0.0f, 400.0f);
}

void AActorPlayerCamera::BeginPlay()
{
	Super::BeginPlay();

	//Get player
	PlayerRef = Cast<APawnPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	// Set view
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC)
	{
		PC->SetViewTarget(this);
	}
}

void AActorPlayerCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PlayerRef)
	{
		return;
	}

	FVector TargetPosition = PlayerRef->GetActorLocation() + DistanceBetweenPlayer;
	TargetPosition.Y = FMath::Clamp(TargetPosition.Y, YLeftLimit, YRightLimit);
	FVector NewLocation = FMath::VInterpTo(GetActorLocation(), TargetPosition, DeltaTime, Speed);

	SetActorLocation(NewLocation);
}