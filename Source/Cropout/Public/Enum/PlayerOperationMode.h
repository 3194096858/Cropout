#pragma once
#include "CoreMinimal.h"

#include "PlayerOperationMode.generated.h"

UENUM(BlueprintType)
enum class EPlayerOperationMode : uint8 {
    None,
    Movement,
    Construction,
    Control
};



