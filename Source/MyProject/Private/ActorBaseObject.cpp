


#include "ActorBaseObject.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

AActorBaseObject::AActorBaseObject()
{
	PrimaryActorTick.bCanEverTick = false;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    SetRootComponent(Root);

    ObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObjectMesh"));
    ObjectMesh->SetupAttachment(Root);



}


void AActorBaseObject::BeginPlay()
{
	Super::BeginPlay();
	
}


void AActorBaseObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

