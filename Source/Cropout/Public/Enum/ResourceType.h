#pragma once
#include "CoreMinimal.h"
#include "ResourceType.generated.h"


UENUM(BlueprintType)
enum class EResourceType : uint8
{
	None,
	Wood,
	Stone,
	Food
};
