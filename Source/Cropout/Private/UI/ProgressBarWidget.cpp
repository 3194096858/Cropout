

#include "UI/ProgressBarWidget.h"



#include "Components/ProgressBar.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"



void UProgressBarWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	this->ProgressBar->SetVisibility(ESlateVisibility::HitTestInvisible);
	this->SizeBox->SetRenderOpacity(0.0f);
	if (this->IsShowText == true)
	{
		this->TextBlock->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	else
	{
		this->TextBlock->SetVisibility(ESlateVisibility::Hidden);
	}

}


void UProgressBarWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	this->FontInformation.TypefaceFontName = this->TextBlock->GetFont().TypefaceFontName;
	this->FontInformation.FontObject = this->TextBlock->GetFont().FontObject;
	this->TextBlock->SetText(this->Text);
	this->TextBlock->SetFont(this->FontInformation);
	if (this->IsShowText == true)
	{
		this->TextBlock->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	else
	{
		this->TextBlock->SetVisibility(ESlateVisibility::Hidden);
	}
	/*this->Style.BackgroundImage.DrawAs = ESlateBrushDrawType::RoundedBox;
	this->Style.BackgroundImage.OutlineSettings.RoundingType = ESlateBrushRoundingType::FixedRadius;
	this->Style.BackgroundImage.OutlineSettings.CornerRadii = FVector4(10.0f);
	this->Style.BackgroundImage.OutlineSettings.Width = 0.0f;
	this->Style.BackgroundImage.OutlineSettings.Color = FColor::Black;
	this->Style.FillImage.DrawAs = ESlateBrushDrawType::RoundedBox;
	this->Style.FillImage.OutlineSettings.RoundingType = ESlateBrushRoundingType::FixedRadius;
	this->Style.FillImage.OutlineSettings.CornerRadii = FVector4(10.0f);
	this->Style.FillImage.OutlineSettings.Width = 3.0f;
	this->Style.FillImage.OutlineSettings.Color = FColor(0.02f,0.5f,0.0f,1.0f);*/

	//this->ProgressBar->SetWidgetStyle(this->Style);
	//this->ProgressBar->SetBarFillStyle();
	//this->ProgressBar->SetPercent();
}


void UProgressBarWidget::NativeDestruct()
{
	Super::NativeDestruct();

}

void UProgressBarWidget::InitializeAnimation(UWidgetAnimation* Animation_FadeIn)
{
	this->FadeInAnimation = Animation_FadeIn;
	if (this->FadeInAnimation == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UTextBlockWidget::InitializeAnimation(): this->FadeInAnimation == nullptr"));
	}

}


void UProgressBarWidget::PlayFadeInAnimation(float PlayRate)
{
	PlayAnimation(this->FadeInAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward, PlayRate);
}

void UProgressBarWidget::PlayFadeOutAnimation(float PlayRate)
{
	PlayAnimation(this->FadeInAnimation, 0.0f, 1, EUMGSequencePlayMode::Reverse, PlayRate);
}

void UProgressBarWidget::SetBackGroundImageStyle(ESlateBrushDrawType::Type DrawType, ESlateBrushRoundingType::Type RoundingType, const FVector4& CornerRadious, float Width, const FColor& ImageColor)
{
	this->Style.BackgroundImage.DrawAs = DrawType;
	this->Style.BackgroundImage.OutlineSettings.RoundingType = RoundingType;
	this->Style.BackgroundImage.OutlineSettings.CornerRadii = CornerRadious;
	this->Style.BackgroundImage.OutlineSettings.Width = Width;
	this->Style.BackgroundImage.OutlineSettings.Color = ImageColor;
	//this->Style.BackgroundImage.SetResourceObject
	//this->Style.BackgroundImage.Ima

}


void UProgressBarWidget::SetFillImageStyle(ESlateBrushDrawType::Type DrawType, ESlateBrushRoundingType::Type RoundingType, const FVector4& CornerRadious, float Width, const FColor& ImageColor)
{
	this->Style.FillImage.DrawAs = DrawType;
	this->Style.FillImage.OutlineSettings.RoundingType = RoundingType;
	this->Style.FillImage.OutlineSettings.CornerRadii = CornerRadious;
	this->Style.FillImage.OutlineSettings.Width = Width;
	this->Style.FillImage.OutlineSettings.Color = ImageColor;
}


void UProgressBarWidget::SetPercent(float NewPercent)
{
    this->ProgressBar->SetPercent(NewPercent);
}



void UProgressBarWidget::SetSize(float Width, float Height)
{
    this->SizeBox->SetWidthOverride(Width);
    this->SizeBox->SetHeightOverride(Height);

}


float UProgressBarWidget::GetWidth()
{
	return this->SizeBox->GetWidthOverride();
}

float UProgressBarWidget::GetHeight()
{
	return this->SizeBox->GetHeightOverride();
}


float UProgressBarWidget::GetSizeBoxRenderOpacity()
{
    return this->SizeBox->GetRenderOpacity();
}






