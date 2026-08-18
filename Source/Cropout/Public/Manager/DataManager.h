
#pragma once
#include "Enum/ResourceType.h"
#include "Enum/NPCState/NPCState.h"
#include "Enum/GameObjectType/GameObjectType.h"
#include "Enum/GameStatus.h"


#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DataManager.generated.h"

namespace EPathFollowingStatus { enum Type : int; };


USTRUCT(BlueprintType)
struct FAudioSettingsData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,SaveGame)
	float SFXVolume = 1.0f;
	UPROPERTY(EditAnywhere, SaveGame)
	float MinSFXVolume = 1.0f;
	UPROPERTY(EditAnywhere, SaveGame)
	float MaxSFXVolume = 1.0f;
	UPROPERTY(EditAnywhere, SaveGame)
	float BGMVolume = 1.0f;
	UPROPERTY(EditAnywhere, SaveGame)
	float MinBGMVolume = 1.0f;
	UPROPERTY(EditAnywhere, SaveGame)
	float MaxBGMVolume = 1.0f;



};

USTRUCT(BlueprintType)
struct FOperationSettingsData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, SaveGame)
	FVector2D ScreenPosition = FVector2D(0.0f);
	UPROPERTY(EditAnywhere, SaveGame)
	FVector2D ScreenPositionXRange = FVector2D(-5000.0f,5000.0f);
	UPROPERTY(EditAnywhere, SaveGame)
	FVector2D ScreenPositionYRange = FVector2D(-5000.0f,5000.0f);
	UPROPERTY(EditAnywhere, SaveGame)
	float ScreenMovementRate = 40.0f;
	UPROPERTY(EditAnywhere, SaveGame)
	float MinScreenMovementRate = 40.0f;
	UPROPERTY(EditAnywhere, SaveGame)
	float MaxScreenMovementRate= 100.0f;
	UPROPERTY(EditAnywhere, SaveGame)
	float MinScreenScaleRate = 100.0f;
	UPROPERTY(EditAnywhere, SaveGame)
	float MaxScreenScaleRate = 120.0f;
	UPROPERTY(EditAnywhere, SaveGame)
	float ScreenScaleRate = 100.0f;
	UPROPERTY(EditAnywhere, SaveGame)
	float ScreenScale = 7000.0f;
	UPROPERTY(EditAnywhere, SaveGame)
	float MaxScreenScale = 9000.0f;
	UPROPERTY(EditAnywhere, SaveGame)
	float MinScreenScale = 2000.0f;

};


USTRUCT(BlueprintType)
struct FGameSettingsData
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, SaveGame)
	FAudioSettingsData Audio;
	UPROPERTY(EditAnywhere, SaveGame)
	FOperationSettingsData Operation;
};




USTRUCT(BlueprintType)
struct FPlayerData
{
	GENERATED_BODY()
public:
	UPROPERTY( SaveGame)
	TMap<EResourceType, int32> ResourceMap;
	UPROPERTY(EditAnywhere, SaveGame)
	TMap<EResourceType, int32> MaxResourceMap;
	UPROPERTY(EditAnywhere, SaveGame)
	FTransform Transform;


};


USTRUCT(BlueprintType)
struct FAnimationData
{
	GENERATED_BODY()
public:
    UPROPERTY(SaveGame)
	bool IsActive = false;
	UPROPERTY(SaveGame)
	float Position = 0.0f;
    UPROPERTY(SaveGame)
	float PlayRate = 1.0f;
	UPROPERTY(SaveGame)
	FName StectionName;
};
USTRUCT(BlueprintType)
struct FNPCBehaviorTreeData
{
	GENERATED_BODY()
public:
	UPROPERTY(SaveGame)
	ENPCState NPCState = ENPCState::None;
	UPROPERTY(SaveGame)
	ENPCState NPCStateBeforeTransport = ENPCState::None;
	UPROPERTY(SaveGame)
	FVector GameObjectLocation;
	UPROPERTY(SaveGame)
	FVector TownHallLocation;
	UPROPERTY(SaveGame)
	FVector RandomLocation;
	UPROPERTY(SaveGame)
	bool IsCompleteJob = true;
	UPROPERTY(SaveGame)
	bool IsCropMature = false;
	UPROPERTY(SaveGame)
	float DistanceBetweenSelfAndObject = 0.0f;
	UPROPERTY(SaveGame)
	TEnumAsByte<EPathFollowingStatus::Type> PathFollowingStatus;

};

USTRUCT(BlueprintType)
struct FVillagerData
{
	GENERATED_BODY()
public:
	UPROPERTY(SaveGame)
	FNPCBehaviorTreeData BehaviorTreeData;
    UPROPERTY(SaveGame)
	FAnimationData AnimationData;
	UPROPERTY(SaveGame)
	FTransform Transform;
	UPROPERTY(SaveGame)
	EGameObjectType GameObjectType = EGameObjectType::None;
	UPROPERTY(SaveGame)
	FVector GameObjectLocation;
	UPROPERTY(SaveGame)
	TMap<EResourceType, int32> ResourceMap;
	UPROPERTY(EditAnywhere, SaveGame)
	TMap<EResourceType, int32> MaxResourceMap;
	UPROPERTY(EditAnywhere, SaveGame)
	float MinAttack = 0.0f;
	UPROPERTY(EditAnywhere, SaveGame)
	float MaxAttack = 10.0f;
	UPROPERTY(EditAnywhere, SaveGame)
	float MaxMovementSpeed = 500.0f;
	UPROPERTY(SaveGame)
	bool IsWeaponVisible = false;
	UPROPERTY(SaveGame)
	bool IsHatVisible = false;
	UPROPERTY(SaveGame)
	int32 FoodConsumption = 10;
};

USTRUCT(BlueprintType)
struct FGameObjectData
{
	GENERATED_BODY()
public:
	UPROPERTY(SaveGame)
	FTransform Transform;
	UPROPERTY(SaveGame)
	float Health = 0.0f;
	UPROPERTY(EditAnywhere,SaveGame)
	float MaxHealth = 0.0f;
	UPROPERTY(SaveGame)
	int32 MeshIndex = -1;


};

USTRUCT(BlueprintType)
struct FFieldBaseData : public FGameObjectData
{
	GENERATED_BODY()
public:
	UPROPERTY(SaveGame)
	int32 Maturation = 0;
	UPROPERTY(SaveGame)
	int32 MaxMaturation = 0;

};

USTRUCT(BlueprintType)
struct FTownHallData : public FGameObjectData
{
	GENERATED_BODY()
public:
	UPROPERTY(SaveGame)
	TArray<FName> VillagerNameArray;

};




UCLASS(Blueprintable,BlueprintType)
class CROPOUT_API UDataManager : public UObject
{
	GENERATED_BODY()
public:
    UDataManager();

public:
	UPROPERTY(EditAnywhere)
	FGameSettingsData DefaultGameSettingsData;
    UPROPERTY(EditAnywhere)
	FPlayerData DefaultPlayerData;
    UPROPERTY(EditAnywhere)
	FVillagerData DefaultVillagerData;
	UPROPERTY(EditAnywhere)
	FGameObjectData DefaultGameObjectData;
	UPROPERTY(EditAnywhere)
	FTownHallData DefaultTownHallData;
	UPROPERTY(EditAnywhere)
	FFieldBaseData DefaultFieldBaseData;

private:
	FTownHallData TownHallData;
	FPlayerData PlayerData;
	TMap<FName, FFieldBaseData> FieldBaseDataMap;
	TMap<FName, FGameObjectData> GameObjectDataMap;
	TMap<FName,FVillagerData> VillagerDataMap;
	FGameSettingsData GameSettingsData;
	int32 VillagerCount = 0;
	EGameStatus GameStatus = EGameStatus::None;
	int32 PlayTime = 0;
public:
	UFUNCTION()
	int32 GetPlayTime();
	UFUNCTION()
	void SetPlayTime(int32 NewValue);
	UFUNCTION()
	void ResetAllData();
	UFUNCTION()
	void SetGameStatus(EGameStatus NewStatus);
	UFUNCTION()
	EGameStatus GetGameStatus();
	UFUNCTION()
	void CreateFieldBaseData(FName ActorName);
	UFUNCTION()
	void DeleteFieldBaseData(FName ActorName);
	UFUNCTION()
	FFieldBaseData& GetFieldBaseData(FName ActorName);
	UFUNCTION()
	void UpdateFieldBaseData(FName ActorName, FFieldBaseData NewData);
	UFUNCTION()
	bool CheckFieldBaseDataIsExist(FName ActorName);
	UFUNCTION()
	FTownHallData& GetTownHallData();
	UFUNCTION()
	void UpdateTownHallData(const FTownHallData& NewData);
	UFUNCTION()
	bool CheckGameObjectDataIsExist(FName ActorName);
	UFUNCTION()
	bool CheckVillagerDataIsExist(FName ActorName);
	UFUNCTION()
	void CreateGameObjectData(FName ActorName);
	UFUNCTION()
	void DeleteGameObjectData(FName ActorName);
	UFUNCTION()
	FGameObjectData& GetGameObjectData(FName ActorName);
	UFUNCTION()
	void UpdateGameObjectData(FName ActorName, FGameObjectData NewData);
	UFUNCTION()
	void CreateVillagerData(FName ActorName);
    UFUNCTION()
	void DeleteVillagerData(FName ActorName);
	UFUNCTION()
	FVillagerData& GetVillagerData(FName ActorName);
	UFUNCTION()
	void UpdateVillagerData(FName ActorName, FVillagerData NewData);
    UFUNCTION()
	FPlayerData& GetPlayerData();
	UFUNCTION()
	void UpdatePlayerData(const FPlayerData& NewData);
	UFUNCTION()
	int32 GetVillagerCount();
	UFUNCTION()
	void SetVillagerCount(int32 NewValue);
	UFUNCTION()
	FGameSettingsData& GetGameSettingsData();
	UFUNCTION()
	void UpdateGameSettingsData(FGameSettingsData NewData);
	UFUNCTION()
	void SaveGameProgress();
	UFUNCTION()
	void DeleteSaveGame(const FString& SaveGameName,int32 Index);
	UFUNCTION()
	void LoadGameProgress();
	UFUNCTION()
	bool CheckSaveGameIsExist(const FString& SaveGameName ,int32 Index);
	UFUNCTION()
	void SaveGameSettings();
	UFUNCTION()
	void LoadGameSettings();





};
