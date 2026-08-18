#pragma once


#include "CoreMinimal.h"
#include "WidgetType.generated.h"


UENUM(BlueprintType)
enum class EWidgetType : uint8
{
    None,
    Construction,
    Start,
    Battle,
    Pause,
    Victory,
    Failure,
    UserTip,
    BackGround,
    Load,
    TextBlock,
    ProgressBar
};


