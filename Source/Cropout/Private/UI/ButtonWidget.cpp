#include "UI/ButtonWidget.h"


#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"



void UButtonWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	this->Button->OnClicked.AddDynamic(this, &UButtonWidget::OnClickButton);
	this->Image->SetVisibility(ESlateVisibility::HitTestInvisible);
    this->TextBlock->SetVisibility(ESlateVisibility::HitTestInvisible);
	
}


void UButtonWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	this->Image->SetBrushFromTexture(IconTexture);
	FSlateFontInfo Font;
	Font = this->TextBlock->GetFont();
    Font.Size = FontSize;
    this->TextBlock->SetText(Text);
	this->TextBlock->SetFont(Font);
	FButtonStyle ButtonStyle;
	ButtonStyle.SetNormal(this->NormalStyle);
	ButtonStyle.SetHovered(this->HoverStyle);
	ButtonStyle.SetPressed(this->PressStyle);
	this->Button->SetStyle(ButtonStyle);
	if(this->IsShowIcon == true)
	{
		this->Image->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	else
	{
		this->Image->SetVisibility(ESlateVisibility::Hidden);
	}
    if(this->IsShowText == true)
    {
        this->TextBlock->SetVisibility(ESlateVisibility::HitTestInvisible);
    }
    else
    {
        this->TextBlock->SetVisibility(ESlateVisibility::Hidden);
    }
	
}


void UButtonWidget::NativeDestruct()
{
	Super::NativeDestruct();

}


void UButtonWidget::OnClickButton()
{
	this->OnClick.ExecuteIfBound();
}










