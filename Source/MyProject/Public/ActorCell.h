
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorCell.generated.h"

UCLASS()
class MYPROJECT_API AActorCell : public AActor
{
	GENERATED_BODY()
	
public:	
	AActorCell();

protected:

	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


	bool IsPlayerHere;
	bool Occupied;
	FVector CellCenterLocation;

};
