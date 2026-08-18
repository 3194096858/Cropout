#include "UI/UserTipWidget.h"


#include "GameMode/CropoutGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Manager/DelegateManager.h"
#include "GameInstance/CropoutGameInstance.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "Manager/WidgetManager.h"
#include "Animation/WidgetAnimation.h"
#include "UI/TextBlockWidget.h"
#include "Components/CanvasPanelSlot.h"



void UUserTipWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	this->CropoutGameMode = Cast<ACropoutGameMode>(UGameplayStatics::GetGameMode(this));
	if (this->CropoutGameMode == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UUserTipWidget::NativeOnInitialized(): CropoutGameMode == nullptr"));
		return;
	}
	this->PlacementTip->SetVisibility(ESlateVisibility::Hidden);
	this->SaveGameTip->SetVisibility(ESlateVisibility::Hidden);
	this->ResourceTip->SetVisibility(ESlateVisibility::Hidden);
	this->ObjectCountTip->SetVisibility(ESlateVisibility::Hidden);


}



void UUserTipWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	
}


void UUserTipWidget::NativeDestruct()
{
	Super::NativeDestruct();

}

void UUserTipWidget::InitializeAnimation(UWidgetAnimation* Animation_PlacementTip, UWidgetAnimation* Animation_SaveGameTip, UWidgetAnimation* Animation_ResourceTip, UWidgetAnimation* Animation_ObjectCountTip)
{
	this->PlacementTipAnimation = Animation_PlacementTip;
	this->SaveGameTipAnimation = Animation_SaveGameTip;
	this->ResourceTipAnimation = Animation_ResourceTip;
    this-> ObjectCountTipAnimation = Animation_ObjectCountTip;
	if (this->PlacementTipAnimation == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UUserTipWidget::InitializeAnimation(): PlacementTipAnimation  == nullptr"));
		return;
	}
	if(this->SaveGameTipAnimation == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UUserTipWidget::InitializeAnimation(): SaveGameTipAnimation  == nullptr"));
		return;
	}
	if(this->ResourceTipAnimation == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UUserTipWidget::InitializeAnimation(): ResourceTipAnimation  == nullptr"));
		return;
	}
	if(this->ObjectCountTipAnimation == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UUserTipWidget::InitializeAnimation(): ObjectCountTipAnimation  == nullptr"));
	}
}


void UUserTipWidget::DisplayObjectCountTip()
{
	this->ObjectCountTip->SetVisibility(ESlateVisibility::Visible);
	PlayAnimation(this->ObjectCountTipAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f);

}

void UUserTipWidget::DisplayResourceTip()
{
	this->ResourceTip->SetVisibility(ESlateVisibility::Visible);
	PlayAnimation(this->ResourceTipAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f);

}

void UUserTipWidget::DisplayPlacementTip()
{
	this->PlacementTip->SetVisibility(ESlateVisibility::Visible);
	PlayAnimation(this->PlacementTipAnimation,0.0f,1,EUMGSequencePlayMode::Forward,1.0f);

}


void UUserTipWidget::DisplaySaveGameTip()
{
	this->SaveGameTip->SetVisibility(ESlateVisibility::Visible);
	PlayAnimation(this->SaveGameTipAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward, 2.0f);

}


void UUserTipWidget::AddWidgetToCanvasPanel(UUserWidget* Widget)
{
	UPanelSlot* PanelSlot = nullptr;
	UCanvasPanelSlot* CanvasPanelSlot = nullptr;
	PanelSlot = this->CanvasPanel->AddChild(Widget);
	if (PanelSlot == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UUserTipWidget::AddWidgetToCanvasPanel(): Slot == nullptr"));
		return;
	}
	CanvasPanelSlot = Cast<UCanvasPanelSlot>(PanelSlot);
	CanvasPanelSlot->SetAutoSize(true);

}

void UUserTipWidget::RemoveWidgetFromCanvasPanel(UUserWidget* Widget)
{
	this->CanvasPanel->RemoveChild(Widget);

}

void UUserTipWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	Super::OnAnimationFinished_Implementation(Animation);
	if (Animation == this->PlacementTipAnimation)
	{
		this->PlacementTip->SetVisibility(ESlateVisibility::Hidden);

	}
	


}

