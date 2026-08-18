#include "GameInstance/CropoutGameInstance.h"
#include "Manager/DelegateManager.h"
#include "Manager/DecalManager.h"
#include "Manager/WidgetManager.h"
#include "Manager/DataManager.h"

#include "Manager/LevelManager.h"

UCropoutGameInstance::UCropoutGameInstance()
{
	
}

void UCropoutGameInstance::Init()
{
	Super::Init();
	InitializeManager();

}


void UCropoutGameInstance::OnStart()
{
	Super::OnStart();
	this->LevelManager->InitializeLevelPathMap();


}

void UCropoutGameInstance::InitializeManager()
{
	DelegateManager = NewObject<UDelegateManager>(this);
	DecalManager = NewObject<UDecalManager>(this);
	WidgetManager = NewObject<UWidgetManager>(this);
	DataManager = NewObject<UDataManager>(this);
	LevelManager = NewObject<ULevelManager>(this);

	if (DelegateManager==nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UCropoutGameInstance::InitializeManager(): DelegateManager == nullptr"));
	}
	if (DecalManager == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UCropoutGameInstance::InitializeManager(): DecalManager == nullptr"));
	}
	if (WidgetManager == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UCropoutGameInstance::InitializeManager(): WidgetManager == nullptr"));
	}
	if (DataManager == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UCropoutGameInstance::InitializeManager(): DataManager == nullptr"));
	}
	if (LevelManager == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UCropoutGameInstance::InitializeManager(): LevelManager == nullptr"));
	}
}





















