

#include "UI/StartWidget.h"


#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "UI/ButtonWidget.h"
#include "Components/SizeBox.h"
#include "GameMode/CropoutGameMode.h"
#include "GameInstance/CropoutGameInstance.h"
#include "Manager/DelegateManager.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/WidgetManager.h"
#include "Animation/WidgetAnimation.h"
#include "Animation/WidgetAnimationEvents.h"
#include "Manager/DataManager.h"
#include "Manager/LevelManager.h"


void UStartWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	this->ContinuationButton->OnClick.BindUObject(this, &UStartWidget::OnClickContinuationButton);
    this->NewGameButton->OnClick.BindUObject(this, &UStartWidget::OnClickNewGameButton);
    this->QuitButton->OnClick.BindUObject(this, &UStartWidget::OnClickQuitButton);
    this->ConfirmedButton->OnClick.BindUObject(this, &UStartWidget::OnClickConfirmedButton);
    this->ReturnButton->OnClick.BindUObject(this, &UStartWidget::OnClickReturnButton);
	this->CropoutGameMode = Cast<ACropoutGameMode>(UGameplayStatics::GetGameMode(this));
	if (this->CropoutGameMode == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UStartWidget::NativeOnInitialized(): CropoutGameMode == nullptr"));
		return;
	}
	this->SaveGameWarningPanel->SetVisibility(ESlateVisibility::Hidden);

}


void UStartWidget::NativeConstruct()
{
	Super::NativeConstruct();
	OpenStartPanel();
	if (this->CropoutGameMode->GetGameInstance()->GetDataManager()->CheckSaveGameIsExist(FString("GameProgressSaveGame"), 0) ==false)
	{
		this->ContinuationButton->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		this->ContinuationButton->SetVisibility(ESlateVisibility::Visible);
	}


}

void UStartWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	
}

void UStartWidget::NativeDestruct()
{
	Super::NativeDestruct();

}


void UStartWidget::InitializeAnimation(UWidgetAnimation* Animation_StartPanel, UWidgetAnimation* Animation_SaveGameWarningPanel)
{
    this->StartPanelAnimation = Animation_StartPanel;
    this->SaveGameWarningPanelAnimation = Animation_SaveGameWarningPanel;
	if (this->StartPanelAnimation == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UStartWidget::InitializeAnimation(): StartPanelAnimation == nullptr"));
        return;
	}
    if (this->SaveGameWarningPanelAnimation == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("UStartWidget::InitializeAnimation(): SaveGameWarningPanelAnimation == nullptr"));
        return;
    }
}

void UStartWidget::OpenStartPanel()
{
	this->StartPanel->SetVisibility(ESlateVisibility::Visible);
	PlayAnimation(this->StartPanelAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward, 2.0f);

}

void UStartWidget::CloseStartPanel()
{
	PlayAnimation(this->StartPanelAnimation, 0.0f, 1, EUMGSequencePlayMode::Reverse, 2.0f);

}

void UStartWidget::OpenSaveGameWarningPanel()
{
	this->SaveGameWarningPanel->SetVisibility(ESlateVisibility::Visible);
	PlayAnimation(this->SaveGameWarningPanelAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward, 2.0f);

}

void UStartWidget::CloseSaveGameWarningPanel()
{
	PlayAnimation(this->SaveGameWarningPanelAnimation, 0.0f, 1, EUMGSequencePlayMode::Reverse, 3.0f);

}

void UStartWidget::OnClickContinuationButton()
{
	CloseStartPanel();
	this->CropoutGameMode->GetGameInstance()->GetLevelManager()->LoadLevel(this->CropoutGameMode, FName("IslandLevel"));
	this->CropoutGameMode->GetGameInstance()->GetDataManager()->LoadGameProgress();
	this->CropoutGameMode->GetGameInstance()->GetDataManager()->LoadGameSettings();
	auto Lambda = [this]()
		{
			this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameResume.Broadcast(EGameStatus::None);
		};
	GetWorld()->GetTimerManager().ClearTimer(this->DelayTimer);
	GetWorld()->GetTimerManager().SetTimer(this->DelayTimer, Lambda, 1.0f, false);


	
}


void UStartWidget::OnClickNewGameButton()
{
	CloseStartPanel();
	OpenSaveGameWarningPanel();

}


void UStartWidget::OnClickQuitButton()
{
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameQuit.Broadcast();
}


void UStartWidget::OnClickConfirmedButton()
{
	this->CropoutGameMode->GetGameInstance()->GetWidgetManager()->PlayLoadAnimation(EUMGSequencePlayMode::Forward, 1.0f);
	this->CropoutGameMode->GetGameInstance()->GetLevelManager()->LoadLevel(this->CropoutGameMode, FName("IslandLevel"));
	CloseSaveGameWarningPanel();

}


void UStartWidget::OnClickReturnButton()
{
	OpenStartPanel();
	CloseSaveGameWarningPanel();

}


void UStartWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
    Super::OnAnimationFinished_Implementation(Animation);
    if (Animation == this->StartPanelAnimation && this->StartPanel->GetRenderOpacity() == 0.0f)
	{
		this->StartPanel->SetVisibility(ESlateVisibility::Hidden);

	}
	if (Animation == this->SaveGameWarningPanelAnimation && this->SaveGameWarningPanel->GetRenderOpacity() == 0.0f)
	{
		this->SaveGameWarningPanel->SetVisibility(ESlateVisibility::Hidden);

	}
	

}
