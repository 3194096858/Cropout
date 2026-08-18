#pragma once
#include "CoreMinimal.h"


#include "MouseCollisionDetectionType.generated.h"

UENUM(BlueprintType)
enum class EMouseCollisionDetectionType : uint8
{
	None,
	LeftKeyPress,
	LeftKeyRelease,
	RightKeyPress,
	RightKeyRelease,
	MouseMovement,
	MouseWheel
};



