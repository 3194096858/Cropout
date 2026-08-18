

#include "UI/LoadWidget.h"


#include "GameMode/CropoutGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Manager/DelegateManager.h"
#include "GameInstance/CropoutGameInstance.h"
#include "Components/Button.h"
#include "Components/CircularThrobber.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Manager/WidgetManager.h"
#include "Animation/WidgetAnimation.h"
#include "Manager/DataManager.h"

#include "Manager/LevelManager.h"


void ULoadWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	this->BackGroundImage->SetVisibility(ESlateVisibility::HitTestInvisible);
	this->BackGroundImage->SetRenderOpacity(0.0f);
	this->LoadIcon->SetVisibility(ESlateVisibility::HitTestInvisible);
    this->LoadIcon->SetRenderOpacity(0.0f);
	this->CropoutGameMode = Cast<ACropoutGameMode>(UGameplayStatics::GetGameMode(this));
	if (this->CropoutGameMode == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ULoadWidget::NativeOnInitialized(): CropoutGameMode == nullptr"));
		return;
	}
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameCompleteInitialization.AddUObject(this, &ULoadWidget::OnGameCompleteInitialization);
}



void ULoadWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	
}


void ULoadWidget::NativeDestruct()
{
	Super::NativeDestruct();

}



void ULoadWidget::InitializeAnimation(UWidgetAnimation* BackGroundImageFadeIn, UWidgetAnimation* LoadIconFadeIn, UWidgetAnimation* Animation_Load)
{
	this->BackGroundImageFadeInAnimation = BackGroundImageFadeIn;
    this->LoadIconFadeInAnimation = LoadIconFadeIn;
	this->LoadAnimation = Animation_Load;

	if (this->BackGroundImageFadeInAnimation == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ULoadWidget::InitializeAnimation(): BackGroundImageFadeInAnimation == nullptr"));
		return;
	}
    if (this->LoadIconFadeInAnimation == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ULoadWidget::InitializeAnimation(): LoadIconFadeInAnimation == nullptr"));
		return;
	}
}

void ULoadWidget::DisplayBackGroundImage()
{
	PlayAnimation(this->BackGroundImageFadeInAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f);
}

void ULoadWidget::HideBackGroundImage()
{
	PlayAnimation(this->BackGroundImageFadeInAnimation, 0.0f, 1, EUMGSequencePlayMode::Reverse, 1.0f);
}

void ULoadWidget::DisplayLoadIcon()
{
	PlayAnimation(this->LoadIconFadeInAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f);
}

void ULoadWidget::HideLoadIcon()
{
	PlayAnimation(this->LoadIconFadeInAnimation, 0.0f, 1, EUMGSequencePlayMode::Reverse, 1.0f);
}


void ULoadWidget::PlayLoadAnimation(EUMGSequencePlayMode::Type PlayMode, float PlayRate)
{
	if(PlayMode == EUMGSequencePlayMode::Forward)
	{
		DisplayBackGroundImage();
	}
	if (PlayMode == EUMGSequencePlayMode::Reverse)
	{
		HideLoadIcon();

	}
	if (PlayMode == EUMGSequencePlayMode::PingPong)
	{
		PlayAnimation(this->LoadAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f);
	}

}


void ULoadWidget::OnGameCompleteInitialization()
{


}


void ULoadWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	Super::OnAnimationFinished_Implementation(Animation);
	if (Animation == this->BackGroundImageFadeInAnimation)
	{
		if (this->BackGroundImage->GetRenderOpacity() == 1.0f)
		{
			DisplayLoadIcon();
			this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameStartInitialization.Broadcast();
		}
		else
		{
			this->CropoutGameMode->GetGameInstance()->GetDataManager()->SetGameStatus(EGameStatus::GameStart);
			this->CropoutGameMode->GetGameInstance()->GetDataManager()->ResetAllData();
			this->CropoutGameMode->GetGameInstance()->GetDataManager()->LoadGameSettings();
			auto Lambda = [this]()
				{
					this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameStart.Broadcast();
				};
			GetWorld()->GetTimerManager().ClearTimer(this->DelayTimer);
			GetWorld()->GetTimerManager().SetTimer(this->DelayTimer, Lambda, 1.0f, false);


		}
	}

	if (Animation == this->LoadIconFadeInAnimation)
	{
		if (this->LoadIcon->GetRenderOpacity() == 0.0f)
		{
			this->CropoutGameMode->GetGameInstance()->GetWidgetManager()->UpdateBackGroundIamge(EWidgetType::None);
			HideBackGroundImage();
		}
	}

	if (Animation == this->LoadAnimation)
	{
		if (this->LoadIcon->GetRenderOpacity() == 1.0f)
		{
			auto Lambda = [this]()
			{
					PlayAnimation(this->LoadAnimation, 0.0f, 1, EUMGSequencePlayMode::Reverse, 1.0f);
			};
			GetWorld()->GetTimerManager().SetTimer(this->DelayTimer, Lambda, 2.0f, false);
			EGameStatus GameStatus = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetGameStatus();
			if (GameStatus !=EGameStatus::None)
			{
				this->CropoutGameMode->GetGameInstance()->GetDataManager()->SetGameStatus(EGameStatus::None);
				this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnPlayerReturnStartMenu.Broadcast();
			}
			else
			{
				
				this->CropoutGameMode->GetGameInstance()->GetWidgetManager()->RemoveTopWidgetFromViewport();
				this->CropoutGameMode->GetGameInstance()->GetWidgetManager()->AddBattleWidgetToViewport();
				this->CropoutGameMode->GetGameInstance()->GetDataManager()->SetGameStatus(EGameStatus::GameStart);

			}
		}
	}

}














