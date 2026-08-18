
#pragma once
#include "Manager/DataManager.h"

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GameProgressSaveGame.generated.h"



UCLASS()
class CROPOUT_API UGameProgressSaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UPROPERTY(SaveGame)
	FTownHallData TownHallData;
	UPROPERTY(SaveGame)
	FPlayerData PlayerData;
	UPROPERTY(SaveGame)
	TMap<FName, FGameObjectData> GameObjectDataMap;
	UPROPERTY(SaveGame)
	TMap<FName, FVillagerData> VillagerDataMap;
	UPROPERTY(SaveGame)
	TMap<FName, FFieldBaseData> FieldBaseDataMap;
	UPROPERTY(SaveGame)
	int32 VillagerTotal = 0;
	UPROPERTY(SaveGame)
	int32 PlayTime = 0;
private:
	

};
