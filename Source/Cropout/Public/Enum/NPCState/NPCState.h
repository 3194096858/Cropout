#pragma once



#include "CoreMinimal.h"

#include "NPCState.generated.h"

UENUM(BlueprintType)
enum class ENPCState : uint8
{
	None,
	Patrol,
	Woodcutting,
	Mining,
	Gathering,
	Construction,
	Farming,
	Transport
};
