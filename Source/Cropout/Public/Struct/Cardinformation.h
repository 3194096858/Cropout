#pragma once

#include "Enum/GameObjectType/GameObjectType.h"

#include "Enum/ResourceType.h"

#include "CoreMinimal.h"
#include "Cardinformation.generated.h"

class UTexture2D;

USTRUCT(BlueprintType)
struct FCardInformation : public FTableRowBase
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere)
    FName Name;
    UPROPERTY(EditAnywhere)
    UTexture2D* Icon;
    UPROPERTY(EditAnywhere)
    TMap<EResourceType, int32> CostMap;
  
    FCardInformation()
    {
        Name = FName();
        Icon = nullptr;
        CostMap = TMap<EResourceType, int32>();
    }



};
