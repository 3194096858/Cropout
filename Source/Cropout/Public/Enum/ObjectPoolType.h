#pragma once
#include "CoreMinimal.h"

#include "ObjectPoolType.generated.h"

UENUM(BlueprintType)
enum class EObjectPoolType : uint8
{

	None,
	CircleRing,
	GuidanceLineSegment,
	Grass,
	Tree,
	Stone,
	Shrub,
	CornField,
	WheatField,
	LettuceField,
	PumpkinField,
	TownHall,
	VillagerHouse,
	Monument,
	Villager,
	PlaceHolder
};


