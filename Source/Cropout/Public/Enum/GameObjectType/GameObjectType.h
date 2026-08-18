#pragma once
#include "CoreMinimal.h"

#include "GameObjectType.generated.h"

UENUM(BlueprintType)
enum class EGameObjectType : uint8
{
	None,
	Grass,
	Tree,
	Stone,
	Shrub,
	WheatField,
	CornField,
	PumpkinField,
	LettuceField,
	TownHall,
	VillagerHouse,
	Monument,
	Ground,
	PlaceHolder
};
