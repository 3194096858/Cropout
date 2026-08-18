

#include "Manager/LevelManager.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameInstance/CropoutGameInstance.h"
#include "SaveGame/GameProgressSaveGame.h"
#include "Navigation/PathFollowingComponent.h"
#include "Engine/LevelStreamingDynamic.h"


void ULevelManager::LoadLevel(UObject* World, FName LevelName)
{
	if (this->LevelPathMap.Find(LevelName) == nullptr)
	{
		return;
	}
	FVector Location = FVector::ZeroVector;
	FRotator Rotation = FRotator::ZeroRotator;
	bool IsSuccess =false;
	FString LevelPath = *this->LevelPathMap.Find(LevelName);
	this->LevelStreaming = ULevelStreamingDynamic::LoadLevelInstance(World,LevelPath,Location,Rotation,IsSuccess);
	if (IsSuccess == false)
	{
		UE_LOG(LogTemp,Warning,TEXT("ULevelManager::LoadLevel():IsSuccess == false "))
	}
}



void ULevelManager::UnloadLevel()
{
	if (this->LevelStreaming == nullptr)
	{
		return;
	}
	this->LevelStreaming->SetShouldBeLoaded(false);
	this->LevelStreaming->SetShouldBeVisible(false);


}




void ULevelManager::InitializeLevelPathMap()
{
	this->LevelPathMap.Add(FName("MainLevel"),TEXT("/Game/Level/MainLevel"));
	this->LevelPathMap.Add(FName("IslandLevel"), TEXT("/Game/Level/IslandLevel"));

}





