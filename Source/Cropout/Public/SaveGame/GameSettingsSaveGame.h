
#pragma once
#include "Manager/DataManager.h"

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GameSettingsSaveGame.generated.h"



UCLASS()
class CROPOUT_API UGameSettingsSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(SaveGame)
	FGameSettingsData GameSettingsData;


};
