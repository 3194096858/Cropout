#pragma once

#include "CoreMinimal.h"
#include "Enum/MouseCollisionDetectionType.h"

#include "PlayerCollisionDetectionInformation.generated.h"

USTRUCT(BlueprintType)
struct FPlayerCollisionDetectionInformation
{ 
    GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	EMouseCollisionDetectionType MouseCollisionDetectionType;

	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypeQueryArray;







};





