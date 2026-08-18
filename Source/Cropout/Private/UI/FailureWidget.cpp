// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FailureWidget.h"




#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "UI/ButtonWidget.h"

#include "GameMode/CropoutGameMode.h"
#include "GameInstance/CropoutGameInstance.h"
#include "Manager/DelegateManager.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/WidgetManager.h"
#include "Manager/DataManager.h"

#include "Manager/LevelManager.h"


void UFailureWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	this->RestartButton->OnClick.BindUObject(this, &UFailureWidget::OnClickRestartButton);
	this->QuitButton->OnClick.BindUObject(this, &UFailureWidget::OnClickQuitButton);
	this->CropoutGameMode = Cast<ACropoutGameMode>(UGameplayStatics::GetGameMode(this));
	if (this->CropoutGameMode == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UFailureWidget::NativeOnInitialized(): CropoutGameMode == nullptr"));
		return;
	}


}

void UFailureWidget::NativeConstruct()
{
	Super::NativeConstruct();
	OpenFailurePanel();
	int32 PlayTime = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetPlayTime();
	int32 Minute = PlayTime / 60;
	int32 Second = PlayTime % 60;
	FString String = FString::FromInt(Minute) + FString(" M ") + FString::FromInt(Second) + FString(" S");
	UE_LOG(LogTemp, Warning, TEXT("Failure!!! PlayTime=  %s"), *String);

}

void UFailureWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	
}

void UFailureWidget::NativeDestruct()
{
	Super::NativeDestruct();
	CloseFailurePanel();
}


void UFailureWidget::InitializeAnimation(UWidgetAnimation* FadeIn)
{
	this->FadeInAnimation = FadeIn;
	if (this->FadeInAnimation == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UStartWidget::InitializeAnimation(): FadeInAnimation == nullptr"));
		return;
	}
	
}


void UFailureWidget::OpenFailurePanel()
{
	PlayAnimation(this->FadeInAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward, 2.0f);
}


void UFailureWidget::CloseFailurePanel()
{
	PlayAnimation(this->FadeInAnimation, 0.0f, 1, EUMGSequencePlayMode::Reverse, 2.0f);
}

void UFailureWidget::OnClickRestartButton()
{
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameRestart.Broadcast();
	this->CropoutGameMode->GetGameInstance()->GetWidgetManager()->RemoveAllWidgetFromViewport();
	this->CropoutGameMode->GetGameInstance()->GetWidgetManager()->PlayLoadAnimation(EUMGSequencePlayMode::Forward, 1.0f);

}


void UFailureWidget::OnClickQuitButton()
{
	//this->CropoutGameMode->GetGameInstance()->GetDataManager()->SetGameStatus(EGameStatus::None);
	this->CropoutGameMode->GetGameInstance()->GetLevelManager()->UnloadLevel();
	this->CropoutGameMode->GetGameInstance()->GetWidgetManager()->PlayLoadAnimation(EUMGSequencePlayMode::PingPong, 1.0f);

}

