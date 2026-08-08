

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorBaseObject.generated.h"

class UStaticMeshComponent;
class USceneComponent;

UCLASS()
class MYPROJECT_API AActorBaseObject : public AActor
{
	GENERATED_BODY()
	
public:	
	AActorBaseObject();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent *ObjectMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* Root;

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

};
