

#include "UI/CardWidget.h"


#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"



void UCardWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	this->Button->OnClicked.AddDynamic(this, &UCardWidget::OnClickButton);
	this->Button->OnHovered.AddDynamic(this, &UCardWidget::OnHoverButton);
	this->Button->OnUnhovered.AddDynamic(this, &UCardWidget::OnUnhoverButton);
	this->CardIcon->SetVisibility(ESlateVisibility::HitTestInvisible);
	this->CardName->SetVisibility(ESlateVisibility::HitTestInvisible);
	this->FoodCost->SetVisibility(ESlateVisibility::HitTestInvisible);
	this->StoneCost->SetVisibility(ESlateVisibility::HitTestInvisible);
	this->WoodCost->SetVisibility(ESlateVisibility::HitTestInvisible);


}


void UCardWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	
}


void UCardWidget::NativeDestruct()
{
	Super::NativeDestruct();

}

void UCardWidget::InitializeAnimation(UWidgetAnimation* Animation_HoverVFX)
{
	this->HoverVFXAnimation = Animation_HoverVFX;
	if (this->HoverVFXAnimation == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UTextBlockWidget::InitializeAnimation(): this->HoverVFXAnimation == nullptr"));
	}

}


FCardInformation& UCardWidget::GetCardInformation()
{
	return this->CardInformation;
}


void UCardWidget::SetCardIcon(UTexture2D* Icon)
{
	this->CardIcon->SetBrushFromTexture(Icon);
	this->CardInformation.Icon = Icon;
}

void UCardWidget::SetCardCost(TMap<EResourceType, int32> CostMap)
{
	this->FoodCost->SetText(FText::FromString(FString::FromInt(*CostMap.Find(EResourceType::Food))));
	this->WoodCost->SetText(FText::FromString(FString::FromInt(*CostMap.Find(EResourceType::Wood))));
	this->StoneCost->SetText(FText::FromString(FString::FromInt(*CostMap.Find(EResourceType::Stone))));
    this->CardInformation.CostMap = CostMap;
}

void UCardWidget::SetCardName(FName Name)
{
	this->CardName->SetText(FText::FromName(Name));
    this->CardInformation.Name = Name;
}




void UCardWidget::OnClickButton()
{
	this->OnClick.ExecuteIfBound();
}




void UCardWidget::OnHoverButton()
{
	this->OnHover.ExecuteIfBound();
	PlayAnimation(this->HoverVFXAnimation,0.0f,1,EUMGSequencePlayMode::Forward,4.0f);
}




void UCardWidget::OnUnhoverButton()
{
	this->OnUnhover.ExecuteIfBound();
	PlayAnimation(this->HoverVFXAnimation, 0.0f, 1, EUMGSequencePlayMode::Reverse, 4.0f);

}


