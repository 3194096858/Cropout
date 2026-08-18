

#include "Manager/DataManager.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameInstance/CropoutGameInstance.h"
#include "SaveGame/GameProgressSaveGame.h"
#include "Navigation/PathFollowingComponent.h"
#include "SaveGame/GameSettingsSaveGame.h"



UDataManager::UDataManager()
{
	this->DefaultPlayerData.ResourceMap.Add(EResourceType::Wood, 5000);
	this->DefaultPlayerData.ResourceMap.Add(EResourceType::Stone, 5000);
	this->DefaultPlayerData.ResourceMap.Add(EResourceType::Food, 300);
	this->DefaultPlayerData.MaxResourceMap.Add(EResourceType::Wood, 9999);
	this->DefaultPlayerData.MaxResourceMap.Add(EResourceType::Stone, 9999);
	this->DefaultPlayerData.MaxResourceMap.Add(EResourceType::Food, 9999);
	this->DefaultPlayerData.Transform.SetLocation(FVector(0.0f,0.0f,100.0f));
	this->DefaultVillagerData.ResourceMap.Add(EResourceType::Wood, 0);
	this->DefaultVillagerData.ResourceMap.Add(EResourceType::Stone, 0);
	this->DefaultVillagerData.ResourceMap.Add(EResourceType::Food, 0);
	this->DefaultVillagerData.MaxResourceMap.Add(EResourceType::Wood, 30);
    this->DefaultVillagerData.MaxResourceMap.Add(EResourceType::Stone, 20);
    this->DefaultVillagerData.MaxResourceMap.Add(EResourceType::Food, 40);
	this->DefaultVillagerData.FoodConsumption = 10;
	this->DefaultGameObjectData.Transform = FTransform(FRotator(0.0f), FVector(0.0f), FVector(1.0f));
	this->GameSettingsData = this->DefaultGameSettingsData;
	this->PlayerData = this->DefaultPlayerData;
	this->TownHallData = this->DefaultTownHallData;

}

void UDataManager::UpdateGameSettingsData(FGameSettingsData NewData)
{
    this->GameSettingsData = NewData;
	
}


void UDataManager::SetPlayTime(int32 NewValue)
{
	this->PlayTime = NewValue;

}

int32 UDataManager::GetPlayTime()
{
	return this->PlayTime;
}


void UDataManager::ResetAllData()
{
	this->PlayTime = 0;
	//this->GameSettingsData = this->DefaultGameSettingsData;
	this->PlayerData = this->DefaultPlayerData;
	this->TownHallData = this->DefaultTownHallData;
	for(auto& Element : this->GameObjectDataMap)
	{
		UpdateGameObjectData(Element.Key,this->DefaultGameObjectData);
	}
	for (auto& Element : this->VillagerDataMap)
	{
		UpdateVillagerData(Element.Key, this->DefaultVillagerData);
	}
	for (auto& Element : this->FieldBaseDataMap)
	{
		UpdateFieldBaseData(Element.Key, this->DefaultFieldBaseData);
	}
	


}


void UDataManager::SetGameStatus(EGameStatus NewStatus)
{
	this->GameStatus = NewStatus;
}


EGameStatus UDataManager::GetGameStatus()
{
	return this->GameStatus;
}


void UDataManager::CreateFieldBaseData(FName ActorName)
{
	if (this->FieldBaseDataMap.Find(ActorName) != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UDataManager::CreateFieldBaseData(): this->FieldBaseDataMap.Find(ActorName) != nullptr"));
		return;
	}
	this->FieldBaseDataMap.Add(ActorName, this->DefaultFieldBaseData);
}

void UDataManager::DeleteFieldBaseData(FName ActorName)
{
	if (this->FieldBaseDataMap.Find(ActorName) == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UDataManager::DeleteFieldBaseData(): this->FieldBaseDataMap.Find(ActorName) == nullptr"));
		return;
	}
	this->FieldBaseDataMap.Remove(ActorName);
}

FFieldBaseData& UDataManager::GetFieldBaseData(FName ActorName)
{
	if (this->FieldBaseDataMap.Find(ActorName) == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UDataManager::GetFieldBaseData(): this->FieldBaseDataMap.Find(ActorName) == nullptr"));
		return this->DefaultFieldBaseData;
	}
	return *this->FieldBaseDataMap.Find(ActorName);
}

void UDataManager::UpdateFieldBaseData(FName ActorName, FFieldBaseData NewData)
{
	if (this->FieldBaseDataMap.Find(ActorName) == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UDataManager::UpdateFieldBaseData(): this->FieldBaseDataMap.Find(ActorName) == nullptr"));
		return;
	}
	FFieldBaseData* OldData = this->FieldBaseDataMap.Find(ActorName);
	//OldData = &NewData;
	OldData->Transform = NewData.Transform;
	OldData->Health = NewData.Health;
	OldData->MaxHealth = NewData.MaxHealth;
	OldData->MeshIndex = NewData.MeshIndex;
	OldData->MaxMaturation = NewData.MaxMaturation;
    OldData->Maturation = NewData.Maturation;
}


bool UDataManager::CheckFieldBaseDataIsExist(FName ActorName)
{
	return this->FieldBaseDataMap.Contains(ActorName);

}


void UDataManager::UpdateTownHallData(const FTownHallData& NewData)
{
	this->TownHallData = NewData;

}

FTownHallData& UDataManager::GetTownHallData()
{
	return this->TownHallData;

}


bool UDataManager::CheckVillagerDataIsExist(FName ActorName)
{
	return this->VillagerDataMap.Contains(ActorName);
   
}

bool UDataManager::CheckGameObjectDataIsExist(FName ActorName)
{
	return this->GameObjectDataMap.Contains(ActorName);

}

void UDataManager::CreateGameObjectData(FName ActorName)
{
	if (this->GameObjectDataMap.Find(ActorName) != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UDataManager::CreateGameObjectData(): this->GameObjectDataMap.Find(ActorName) != nullptr"));
		return;
	}
	this->GameObjectDataMap.Add(ActorName, this->DefaultGameObjectData);
}

void UDataManager::DeleteGameObjectData(FName ActorName)
{
	if (this->GameObjectDataMap.Find(ActorName) == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UDataManager::DeleteGameObjectData(): this->GameObjectDataMap.Find(ActorName) == nullptr"));
		return;
	}
	this->GameObjectDataMap.Remove(ActorName);
}

FGameObjectData& UDataManager::GetGameObjectData(FName ActorName)
{
	if (this->GameObjectDataMap.Find(ActorName) == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UDataManager::GetGameObjectData(): this->GameObjectDataMap.Find(ActorName) == nullptr"));
		return this->DefaultGameObjectData;
	}
	return *this->GameObjectDataMap.Find(ActorName);
}

void UDataManager::UpdateGameObjectData(FName ActorName, FGameObjectData NewData)
{
	if (this->GameObjectDataMap.Find(ActorName) == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UDataManager::UpdateGameObjectData(): this->GameObjectDataMap.Find(ActorName) == nullptr"));
		return;
	}
	FGameObjectData* OldData = this->GameObjectDataMap.Find(ActorName);
	//OldData = &NewData;
	OldData->Transform = NewData.Transform;
	OldData->Health = NewData.Health;
    OldData->MaxHealth = NewData.MaxHealth;
	OldData->MeshIndex = NewData.MeshIndex;
}


void UDataManager::CreateVillagerData(FName ActorName)
{
	if (this->VillagerDataMap.Find(ActorName) != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UDataManager::CreateVillagerData(): this->VillagerDataMap.Find(ActorName) != nullptr"));
		return;
	}
    this->VillagerDataMap.Add(ActorName,this->DefaultVillagerData);
}

void UDataManager::DeleteVillagerData(FName ActorName)
{
	if (this->VillagerDataMap.Find(ActorName) == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UDataManager::DeleteVillagerData(): this->VillagerDataMap.Find(ActorName) == nullptr"));
		return;
	}
	this->VillagerDataMap.Remove(ActorName);

}

FVillagerData& UDataManager::GetVillagerData(FName ActorName)
{
	if( this->VillagerDataMap.Find(ActorName) == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UDataManager::GetVillagerData(): this->VillagerDataMap.Find(ActorName) == nullptr"));
		return this->DefaultVillagerData;
	}
	return *this->VillagerDataMap.Find(ActorName);
}


void UDataManager::UpdateVillagerData(FName ActorName,FVillagerData NewData)
{
	if (this->VillagerDataMap.Find(ActorName) == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UDataManager::UpdateVillagerData(): this->VillagerDataMap.Find(ActorName) == nullptr"));
		return;
	}
	FVillagerData* OldData = this->VillagerDataMap.Find(ActorName);
	//OldData = &NewData;
	OldData->Transform = NewData.Transform;
	OldData->ResourceMap = NewData.ResourceMap;
    OldData->MaxResourceMap = NewData.MaxResourceMap;
	OldData->BehaviorTreeData = NewData.BehaviorTreeData;
	OldData->AnimationData = NewData.AnimationData;
	OldData->GameObjectType = NewData.GameObjectType;
	OldData->MaxMovementSpeed = NewData.MaxMovementSpeed;
    OldData->MaxAttack = NewData.MaxAttack;
	OldData->IsHatVisible = NewData.IsHatVisible;
    OldData->IsWeaponVisible = NewData.IsWeaponVisible;
	OldData->GameObjectLocation = NewData.GameObjectLocation;


}

void UDataManager::UpdatePlayerData(const FPlayerData& NewData)
{
	this->PlayerData = NewData;

}


int32 UDataManager::GetVillagerCount()
{
	return this->VillagerCount;
}


FPlayerData& UDataManager::GetPlayerData() 
{
	return this->PlayerData;
}


void UDataManager::SetVillagerCount(int32 NewValue)
{
	if (NewValue < 0)
	{
		NewValue = 0;
	}
	this->VillagerCount = NewValue;
};

FGameSettingsData& UDataManager::GetGameSettingsData()
{
	return this->GameSettingsData;
}




void UDataManager::SaveGameProgress()
{
	UGameProgressSaveGame* SaveGame = nullptr;
	FString SlotName = TEXT("GameProgressSaveGame");
	if(CheckSaveGameIsExist(SlotName, 0) == true)
	{
		SaveGame = Cast<UGameProgressSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName,0));
	}
	else
	{
		SaveGame = Cast<UGameProgressSaveGame>(UGameplayStatics::CreateSaveGameObject(UGameProgressSaveGame::StaticClass()));
	}
	if (SaveGame == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UDataManager::SaveGameProgress(): SaveGame == nullptr"));
		return;
	}
	SaveGame->TownHallData = this->TownHallData;
	SaveGame->GameObjectDataMap = this->GameObjectDataMap;
    SaveGame->VillagerDataMap = this->VillagerDataMap;
    SaveGame->VillagerTotal = this->VillagerCount;
	SaveGame->PlayerData = this->PlayerData;
	SaveGame->FieldBaseDataMap = this->FieldBaseDataMap;
	SaveGame->PlayTime = this->PlayTime;
	UGameplayStatics::SaveGameToSlot(SaveGame, SlotName, 0);



}



void UDataManager::LoadGameProgress()
{
	UGameProgressSaveGame* SaveGame = nullptr;
	FString SlotName = TEXT("GameProgressSaveGame");
	if (CheckSaveGameIsExist(SlotName, 0) == false)
	{
		return;
	}
	SaveGame = Cast<UGameProgressSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName,0));
	this->GameObjectDataMap = SaveGame->GameObjectDataMap;
    this->VillagerDataMap = SaveGame->VillagerDataMap;
    this->VillagerCount = SaveGame->VillagerTotal;
    this->PlayerData = SaveGame->PlayerData;
	this->TownHallData = SaveGame->TownHallData;
	this->PlayTime = SaveGame->PlayTime;
	this->FieldBaseDataMap = SaveGame->FieldBaseDataMap;

}


void UDataManager::SaveGameSettings()
{
	UGameSettingsSaveGame* SaveGame = nullptr;
	FString SlotName = TEXT("GameSettingsSaveGame");
	if (CheckSaveGameIsExist(SlotName, 0) == true)
	{
		SaveGame = Cast<UGameSettingsSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
	}
	else
	{
		SaveGame = Cast<UGameSettingsSaveGame>(UGameplayStatics::CreateSaveGameObject(UGameSettingsSaveGame::StaticClass()));
	}
	if (SaveGame == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT(" UDataManager::SaveGameSettings(): SaveGame == nullptr"));
		return;
	}
	SaveGame->GameSettingsData= this->GameSettingsData;
	UGameplayStatics::SaveGameToSlot(SaveGame, SlotName, 0);



}



void UDataManager::LoadGameSettings()
{
	UGameSettingsSaveGame* SaveGame = nullptr;
	FString SlotName = TEXT("GameSettingsSaveGame");
	if (CheckSaveGameIsExist(SlotName, 0) == false)
	{
		return;
	}
	SaveGame = Cast<UGameSettingsSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));

	this->GameSettingsData = SaveGame->GameSettingsData;

}


void  UDataManager::DeleteSaveGame(const FString& SaveGameName, int32 Index)
{
	if (UGameplayStatics::DoesSaveGameExist(SaveGameName, Index))
	{
		UGameplayStatics::DeleteGameInSlot(SaveGameName, Index);
	}

}

bool UDataManager::CheckSaveGameIsExist(const FString& SaveGameName, int32 Index)
{
	return UGameplayStatics::DoesSaveGameExist(SaveGameName, Index);
}

