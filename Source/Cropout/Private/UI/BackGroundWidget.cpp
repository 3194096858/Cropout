

#include "UI/BackGroundWidget.h"


#include "GameMode/CropoutGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Manager/DelegateManager.h"
#include "GameInstance/CropoutGameInstance.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Manager/WidgetManager.h"
#include "Animation/WidgetAnimation.h"

void UBackGroundWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	this->BackGroundImage->SetVisibility(ESlateVisibility::HitTestInvisible);
	this->CropoutGameMode = Cast<ACropoutGameMode>(UGameplayStatics::GetGameMode(this));
	if (this->CropoutGameMode == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ULoadWidget::NativeOnInitialized(): CropoutGameMode == nullptr"));
		return;
	}
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameCompleteInitialization.AddUObject(this, &UBackGroundWidget::OnGameCompleteInitialization);
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameStart.AddUObject(this, &UBackGroundWidget::OnGameStart);


}



void UBackGroundWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	if(this->PreviewWidgetType == EWidgetType::BackGround||this->PreviewWidgetType == EWidgetType::UserTip||this->PreviewWidgetType == EWidgetType::Battle||this->PreviewWidgetType == EWidgetType::Construction||this->PreviewWidgetType == EWidgetType::Load)
	{
		return;
	}
	SetBackGroundImage(this->PreviewWidgetType);

}


void UBackGroundWidget::NativeDestruct()
{
	Super::NativeDestruct();

}

void UBackGroundWidget::SetBackGroundImage(EWidgetType Widget)
{
	if(Widget == EWidgetType::None)
	{
		this->BackGroundImage->SetVisibility(ESlateVisibility::Hidden);
		return;
	}
	if (this->ImageBrushMap.Find(Widget) == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("BackGroundWidget::NativeOnInitialized() : this->BackGroundImageMap.Find(Widget) == nullptr"));
		return;
	}
	FSlateBrush Brush = *this->ImageBrushMap.Find(Widget);
	this->BackGroundImage->SetVisibility(ESlateVisibility::HitTestInvisible);
	this->BackGroundImage->SetBrush(Brush);
}


void UBackGroundWidget::OnGameCompleteInitialization()
{

}


void UBackGroundWidget::OnGameStart()
{

}



void UBackGroundWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	Super::OnAnimationFinished_Implementation(Animation);
	//if (Animation == FadeInAnimation)
	//{
	//	//UE_LOG(LogTemp, Warning, TEXT(" FadeInAnimation Finished!!!!!"));
	//}
	//

}










