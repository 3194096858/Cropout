

#include "UI/VictoryWidget.h"


#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "UI/ButtonWidget.h"
#include "UI/TextBlockWidget.h"

#include "GameMode/CropoutGameMode.h"
#include "GameInstance/CropoutGameInstance.h"
#include "Manager/DelegateManager.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/WidgetManager.h"
#include "Manager/DataManager.h"
#include "Manager/LevelManager.h"



void UVictoryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	this->ResumeButton->OnClick.BindUObject(this, &UVictoryWidget::OnClickResumeButton);
	this->RestartButton->OnClick.BindUObject(this, &UVictoryWidget::OnClickRestartButton);
	this->QuitButton->OnClick.BindUObject(this, &UVictoryWidget::OnClickQuitButton);
	this->CropoutGameMode = Cast<ACropoutGameMode>(UGameplayStatics::GetGameMode(this));
	if (this->CropoutGameMode == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UPauseWidget::NativeOnInitialized(): CropoutGameMode == nullptr"));
		return;
	}


}



void UVictoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	OpenVictoryPanel();
	int32 Time = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetPlayTime();
	int32 Minute = Time / 60;
	int32 Second = Time % 60;
	FString String = FString::FromInt(Minute) + FString(" M ") + FString::FromInt(Second) + FString(" S");
	this->PlayTime->SetText(FText::FromString(String));
	UE_LOG(LogTemp, Warning, TEXT("Victory!!! PlayTime= %s "), *String);
}

void UVictoryWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	
}

void UVictoryWidget::NativeDestruct()
{
	Super::NativeDestruct();
	CloseVictoryPanel();
}


void UVictoryWidget::InitializeAnimation(UWidgetAnimation* FadeIn)
{
	this->FadeInAnimation = FadeIn;
	if (this->FadeInAnimation == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UStartWidget::InitializeAnimation(): FadeInAnimation == nullptr"));
		return;
	}
	
}


void UVictoryWidget::OpenVictoryPanel()
{
	PlayAnimation(this->FadeInAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward, 2.0f);
}


void UVictoryWidget::CloseVictoryPanel()
{
	PlayAnimation(this->FadeInAnimation, 0.0f, 1, EUMGSequencePlayMode::Reverse, 2.0f);
}

void UVictoryWidget::OnClickResumeButton()
{
	this->CropoutGameMode->GetGameInstance()->GetDataManager()->SetGameStatus(EGameStatus::GameStart);
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameResume.Broadcast(EGameStatus::GamePause);
	//UE_LOG(LogTemp, Warning, TEXT(" GameResume !!!!!"));
}


void UVictoryWidget::OnClickRestartButton()
{
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameRestart.Broadcast();
	this->CropoutGameMode->GetGameInstance()->GetWidgetManager()->RemoveAllWidgetFromViewport();
	this->CropoutGameMode->GetGameInstance()->GetWidgetManager()->PlayLoadAnimation(EUMGSequencePlayMode::Forward, 1.0f);

}


void UVictoryWidget::OnClickQuitButton()
{
	this->CropoutGameMode->GetGameInstance()->GetLevelManager()->UnloadLevel();
	this->CropoutGameMode->GetGameInstance()->GetWidgetManager()->PlayLoadAnimation(EUMGSequencePlayMode::PingPong, 1.0f);

}

