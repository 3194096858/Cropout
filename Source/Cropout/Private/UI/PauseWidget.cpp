

#include "UI/PauseWidget.h"


#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "UI/ButtonWidget.h"
#include "UI/SliderWidget.h"
#include "GameMode/CropoutGameMode.h"
#include "GameInstance/CropoutGameInstance.h"
#include "Manager/DelegateManager.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/WidgetManager.h"
#include "Manager/DataManager.h"
#include "Manager/LevelManager.h"



void UPauseWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	this->ResumeButton->OnClick.BindUObject(this, &UPauseWidget::OnClickResumeButton);
	this->RestartButton->OnClick.BindUObject(this, &UPauseWidget::OnClickRestartButton);
	this->QuitButton->OnClick.BindUObject(this, &UPauseWidget::OnClickQuitButton);
	this->SaveButton->OnClick.BindUObject(this, &UPauseWidget::OnClickSaveButton);
	this->CropoutGameMode = Cast<ACropoutGameMode>(UGameplayStatics::GetGameMode(this));
	this->BGMSlider->OnValueChange.BindUObject(this, &UPauseWidget::OnBGMSliderValueChange);
	this->SFXSlider->OnValueChange.BindUObject(this, &UPauseWidget::OnSFXSliderValueChange);

	if (this->CropoutGameMode == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UPauseWidget::NativeOnInitialized(): CropoutGameMode == nullptr"));
		return;
	}


}

void UPauseWidget::NativeConstruct()
{
	Super::NativeConstruct();
	OpenGamePausePanel();
	FGameSettingsData Data = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetGameSettingsData();
	this->BGMSlider->SetValue(Data.Audio.BGMVolume);
	this->SFXSlider->SetValue(Data.Audio.SFXVolume);



}


void UPauseWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

}

void UPauseWidget::NativeDestruct()
{
	Super::NativeDestruct();
	CloseGamePausePanel();

}


void UPauseWidget::InitializeAnimation(UWidgetAnimation* FadeIn)
{
	this->FadeInAnimation = FadeIn;
	if (this->FadeInAnimation == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UStartWidget::InitializeAnimation(): FadeInAnimation == nullptr"));
		return;
	}
	
}


void UPauseWidget::OpenGamePausePanel()
{
	PlayAnimation(this->FadeInAnimation,0.0f,1,EUMGSequencePlayMode::Forward,2.0f);
}


void UPauseWidget::CloseGamePausePanel()
{
	PlayAnimation(this->FadeInAnimation, 0.0f, 1, EUMGSequencePlayMode::Reverse, 2.0f);
}



void UPauseWidget::OnClickResumeButton()
{
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameResume.Broadcast(EGameStatus::GamePause);
	//UE_LOG(LogTemp, Warning, TEXT(" GameResume !!!!!"));
	this->CropoutGameMode->GetGameInstance()->GetDataManager()->SetGameStatus(EGameStatus::GameStart);

}


void UPauseWidget::OnClickRestartButton()
{
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameRestart.Broadcast();
	this->CropoutGameMode->GetGameInstance()->GetWidgetManager()->RemoveTopWidgetFromViewport();
	this->CropoutGameMode->GetGameInstance()->GetWidgetManager()->PlayLoadAnimation(EUMGSequencePlayMode::Forward, 1.0f);

}


void UPauseWidget::OnClickQuitButton()
{
	//this->CropoutGameMode->GetGameInstance()->GetDataManager()->SetGameStatus(EGameStatus::None);
	this->CropoutGameMode->GetGameInstance()->GetLevelManager()->UnloadLevel();
	this->CropoutGameMode->GetGameInstance()->GetWidgetManager()->PlayLoadAnimation(EUMGSequencePlayMode::PingPong, 1.0f);
	// UE_LOG(LogTemp, Warning, TEXT(" 111111111111111111111111111"));

}


void UPauseWidget::OnClickSaveButton()
{
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameSave.Broadcast();
	this->CropoutGameMode->GetGameInstance()->GetDataManager()->SaveGameProgress();
	this->CropoutGameMode->GetGameInstance()->GetDataManager()->SaveGameSettings();
	this->CropoutGameMode->GetGameInstance()->GetWidgetManager()->AddSaveGameTipToViewport();

}



void UPauseWidget::OnBGMSliderValueChange(float Value)
{
	FGameSettingsData Data = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetGameSettingsData();
	Data.Audio.BGMVolume = Value;
	this->BGMSlider->SetValue(Value);
	this->CropoutGameMode->GetGameInstance()->GetDataManager()->UpdateGameSettingsData(Data);
}


void UPauseWidget::OnSFXSliderValueChange(float Value)
{
	FGameSettingsData Data = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetGameSettingsData();
	Data.Audio.SFXVolume = Value;
	this->SFXSlider->SetValue(Value);
	this->CropoutGameMode->GetGameInstance()->GetDataManager()->UpdateGameSettingsData(Data);

}
