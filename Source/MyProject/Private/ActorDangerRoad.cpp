
#include "ActorDangerRoad.h"
#include "Kismet/GameplayStatics.h"

AActorDangerRoad::AActorDangerRoad()
{

	PrimaryActorTick.bCanEverTick = false;


}

void AActorDangerRoad::BeginPlay()
{
    Super::BeginPlay();

    ChoiseRoadSpeed();
    RoadDirection = GetRandomDirection();
    CarsOnRoad = GetRandCarNums();
    GetCarsPosition();

    for (int32 i = 0;i<CarsOnRoad;i++)
    {
        SpawnCar(i);
    }

}

void AActorDangerRoad::Tick(float DeltaTime)
{


}

FVector AActorDangerRoad::GetRandomDirection()
{
    UE_LOG(RoadLog, Log, TEXT("Function GetRandomDirection called"));
    return FMath::RandBool() ? FVector::LeftVector : FVector::RightVector;
}

int32 AActorDangerRoad::ChoiseRoadSpeed()
{
    UE_LOG(RoadLog, Log, TEXT("Function ChoiseRoadSpeed called"));
    ERoadSpeedType RandSpeed = static_cast<ERoadSpeedType>(FMath::RandRange(0, 2));

    switch (RandSpeed)
    {
    case ERoadSpeedType::Low:
        RoadSpeed = LowSpeed;
        break;

    case ERoadSpeedType::Medium:
        RoadSpeed = MediumSpeed;
        break;

    case ERoadSpeedType::High:
        RoadSpeed = HighSpeed;
        break;

    default:
        RoadSpeed = LowSpeed;
        break;
    }
    UE_LOG(RoadLog, Log, TEXT("Function ChoiseRoadSpeed called,RoadSpeed %i"), RoadSpeed);
    return RoadSpeed;
}

int32 AActorDangerRoad::ChoiseCarToSpawn()
{
    UE_LOG(RoadLog, Log, TEXT("Function ChoiseCarToSpawn called"));
    int32 RandCar = FMath::RandRange(0, AllBPCar.Num() - 1);

    if (AllBPCar.IsValidIndex(RandCar))
    {
        auto CurrentCar = AllBPCar[RandCar];

        if (CurrentCar != nullptr)
        {
            return ChoisedCar = RandCar;
        }
    }
    return -1;
}

int32 AActorDangerRoad::GetRandCarNums()
{
    UE_LOG(RoadLog, Display, TEXT("Function GetRandCarNums called"));
    int32 CarNum = FMath::RandRange(1, 3);
    return CarNum;
}

void AActorDangerRoad::GetCarsPosition()
{
    const TArray<int32> ReadyMadePositions = { -650, -750, -950, -1500 };

    CarPosition.Empty();

    TArray<int32> AvailablePositions = ReadyMadePositions;

    for (int32 i = AvailablePositions.Num() - 1; i > 0; --i)//Random position
    {
        const int32 RandomIndex = FMath::RandRange(0, i);
        AvailablePositions.Swap(i, RandomIndex);
    }

        const int32 NumberOfCars = FMath::Min(CarsOnRoad, AvailablePositions.Num());

    for (int32 i = 0; i < NumberOfCars; ++i)//Fill array
    {
        CarPosition.Add(AvailablePositions[i]);
    }
}

void AActorDangerRoad::SpawnCar(int32 IndexPosition)
{
    UE_LOG(RoadLog, Log, TEXT("Function SpawnCar called"));

    FRotator SpawnRotator;

    if (RoadDirection == FVector::RightVector)//Move from left to right or right to left
    {
        SpawnRotator = FRotator::ZeroRotator;
        SpawnLocation = GetActorLocation() + FVector(0,CarPosition[IndexPosition],0);
    }
    else
    {
        SpawnRotator = FRotator(0.f, 180.f, 0.f);
        SpawnLocation = GetActorLocation() + FVector(0, CarPosition[IndexPosition] * -1, 0);
    }

    int32 RandCarIndex = ChoiseCarToSpawn();

    if (RandCarIndex != -1 && AllBPCar.IsValidIndex(RandCarIndex))
    {
        AActorBaseCar* NewCar = GetWorld()->SpawnActor<AActorBaseCar>(AllBPCar[RandCarIndex], SpawnLocation, SpawnRotator);
            if (NewCar)
            {  
                NewCar->StartLocation = SpawnLocation;
                NewCar->CarSpeed = RoadSpeed;
                NewCar->CarMoveDirection = RoadDirection;
                NewCar->EndY = GetActorLocation().Y +
                    (RoadDirection.Y * 1400.f);

                SpawnedCar.Add(NewCar);
            }
    }
}

void AActorDangerRoad::DeleteCar()
{
     UE_LOG(RoadLog, Log, TEXT("Function DeleteCar called"));
     for (AActorBaseCar* Car : SpawnedCar)
     {
         if (IsValid(Car))
         {
             Car->Destroy();
         }
     }
     SpawnedCar.Empty();
}

void AActorDangerRoad::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    DeleteCar();
}

