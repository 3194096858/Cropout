#pragma once

#include "CoreMinimal.h"
#include "GameStatus.generated.h"



UENUM(BlueprintType)
enum class EGameStatus : uint8
{
	None,
	GameStart,
	GamePause,
	GameOver
};


