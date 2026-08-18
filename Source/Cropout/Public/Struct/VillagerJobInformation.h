#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "VillagerJobInformation.generated.h"

USTRUCT(BlueprintType)
struct FVillagerJobInformation : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	UAnimMontage* Montage;
	UPROPERTY(EditAnywhere)
	UStaticMesh* HatMesh;
	UPROPERTY(EditAnywhere)
	UStaticMesh* WeaponMesh;

    FVillagerJobInformation()
    {
        Montage = nullptr;
        HatMesh = nullptr;
        WeaponMesh = nullptr;
    }
};



