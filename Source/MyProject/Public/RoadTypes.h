

#pragma once

#include "CoreMinimal.h"
#include "RoadTypes.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ERoadType : uint8
{
    SafeRoad    UMETA(DisplayName = "Safe road"),
    DangerRoad    UMETA(DisplayName = "Danger road"),
    TurrelRoad   UMETA(DisplayName = "Turrel road"),
    BaseRoad     UMETA(DisplayName = "Base road")
};