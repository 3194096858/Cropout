

#include "Manager/AudioManager.h"

#include"Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GameInstance/CropoutGameInstance.h"
#include "SaveGame/GameProgressSaveGame.h"
#include "Navigation/PathFollowingComponent.h"
#include "SaveGame/GameSettingsSaveGame.h"

void UAudioManager::PlayBGM(UWorld* World ,USoundBase* Sound)
{
	if (this->AudioComponent == nullptr)
	{
		this->AudioComponent = UGameplayStatics::SpawnSound2D(World, Sound);
	}
	this->AudioComponent->Play();


}



void UAudioManager::PauseBGM()
{
	if (this->AudioComponent == nullptr)
    {
		return;
    }
	if (this->AudioComponent->IsPlaying() == true)
	{
		this->AudioComponent->SetPaused(true);
	}


}