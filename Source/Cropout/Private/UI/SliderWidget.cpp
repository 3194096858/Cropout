// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SliderWidget.h"


#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"

#include "Components/Slider.h"


void USliderWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	this->BackGroundImage->SetVisibility(ESlateVisibility::HitTestInvisible);
	this->Slider->OnValueChanged.AddDynamic(this,&USliderWidget::OnSliderValueChange);

}


void USliderWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	this->BackGroundImage->SetBrush(this->ImageBrush);
	if (this->IsShowBackGroundImage == true)
	{
		this->BackGroundImage->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	else
	{
		this->BackGroundImage->SetVisibility(ESlateVisibility::Hidden);
	}
}


void USliderWidget::NativeDestruct()
{
	Super::NativeDestruct();

}
//
//
//void UTextBlockWidget::InitializeAnimation(UWidgetAnimation* Animation_DamageText)
//{
//	this->DamageTextAnimation = Animation_DamageText;
//	if (this->DamageTextAnimation == nullptr)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("UTextBlockWidget::InitializeAnimation(): this->DamageTextAnimation == nullptr"));
//	}
//
//}




void USliderWidget::SetSize(float Width, float Height)
{
	this->SizeBox->SetWidthOverride(Width);
	this->SizeBox->SetHeightOverride(Height);

}


float USliderWidget::GetWidth()
{
	return this->SizeBox->GetWidthOverride();
}


float USliderWidget::GetHeight()
{
	return this->SizeBox->GetHeightOverride();
}



void USliderWidget::OnSliderValueChange(float Value)
{
	this->OnValueChange.ExecuteIfBound(Value);
}


void USliderWidget::SetValue(float NewValue)
{
	this->Slider->SetValue(NewValue);
}