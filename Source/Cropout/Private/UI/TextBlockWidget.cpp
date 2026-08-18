

#include "UI/TextBlockWidget.h"



#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"



void UTextBlockWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	this->BackGroundImage->SetVisibility(ESlateVisibility::HitTestInvisible);
	this->TextBlock->SetVisibility(ESlateVisibility::HitTestInvisible);
	

}


void UTextBlockWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	this->FontInformation.TypefaceFontName = this->TextBlock->GetFont().TypefaceFontName;
	this->FontInformation.FontObject= this->TextBlock->GetFont().FontObject;
	//this->FontInformation.OutlineSettings
	//this->FontInformation.Colo

	this->BackGroundImage->SetBrush(this->ImageBrush);
    this->TextBlock->SetText(this->Text);
	this->TextBlock->SetFont(this->FontInformation);
	if (this->IsShowBackGroundImage == true)
	{
		this->BackGroundImage->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	else
	{
		this->BackGroundImage->SetVisibility(ESlateVisibility::Hidden);
	}

}


void UTextBlockWidget::NativeDestruct()
{
	Super::NativeDestruct();

}


void UTextBlockWidget::InitializeAnimation(UWidgetAnimation* Animation_DamageText)
{
    this->DamageTextAnimation = Animation_DamageText;
	if(this->DamageTextAnimation == nullptr)
	{
        UE_LOG(LogTemp, Warning, TEXT("UTextBlockWidget::InitializeAnimation(): this->DamageTextAnimation == nullptr"));
	}

}


void UTextBlockWidget::SetFontInformation(float NewSize)
{
	FSlateFontInfo Font;
	Font.Size = NewSize;
	Font.TypefaceFontName = this->TextBlock->GetFont().TypefaceFontName;
    Font.FontObject = this->TextBlock->GetFont().FontObject;
	this->TextBlock->SetFont(Font);



}

void UTextBlockWidget::SetText(FText NewText)
{
    this->Text = NewText;
	this->TextBlock->SetText(NewText);

}

void UTextBlockWidget::SetText(int32 NewText)
{
	this->Text = FText::FromString(FString::FromInt(NewText));
	this->TextBlock->SetText(FText::FromString(FString::FromInt(NewText)));

}


void UTextBlockWidget::PlayDamageTextAnimation(float PlayRate)
{
	PlayAnimation(this->DamageTextAnimation,0.0f,1,EUMGSequencePlayMode::Forward,PlayRate);
}



void UTextBlockWidget::SetSize(float Width, float Height)
{
	this->SizeBox->SetWidthOverride(Width);
	this->SizeBox->SetHeightOverride(Height);

}


float UTextBlockWidget::GetWidth()
{
	return this->SizeBox->GetWidthOverride();
}


float UTextBlockWidget::GetHeight()
{
	return this->SizeBox->GetHeightOverride();
}

float UTextBlockWidget::GetTextBlockRenderOpacity()
{
	return this->TextBlock->GetRenderOpacity();
}
