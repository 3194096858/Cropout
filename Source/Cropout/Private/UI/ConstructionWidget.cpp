

#include "UI/ConstructionWidget.h"

#include "Components/SizeBox.h"
#include "Enum/ResourceType.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "UI/ButtonWidget.h"
#include "UI/CardWidget.h"
#include "GameMode/CropoutGameMode.h"
#include "GameInstance/CropoutGameInstance.h"
#include "Manager/DelegateManager.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/WidgetManager.h"

void UConstructionWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	this->ReturnButton->OnClick.BindUObject(this, &UConstructionWidget::OnClickReturnButton);
	this->CropoutGameMode = Cast<ACropoutGameMode>(UGameplayStatics::GetGameMode(this));
	this->Tree->OnClick.BindUObject(this, &UConstructionWidget::OnClickTree);
    this->Shrub->OnClick.BindUObject(this, &UConstructionWidget::OnClickShrub);
    this->VillagerHouse->OnClick.BindUObject(this, &UConstructionWidget::OnClickVillagerHouse);
	this->Monument->OnClick.BindUObject(this, &UConstructionWidget::OnClickMonument);
	this->CardOperationPanel->SetVisibility(ESlateVisibility::Hidden);
	this->PlacementButton->OnClick.BindUObject(this, &UConstructionWidget::OnClickPlacementButton);
	this->RotationButton->OnClick.BindUObject(this, &UConstructionWidget::OnClickRotationButton);
	this->CancelButton->OnClick.BindUObject(this, &UConstructionWidget::OnClickCancelButton);
	this->WheatField->OnClick.BindUObject(this, &UConstructionWidget::OnClickWheatField);
	this->CornField->OnClick.BindUObject(this, &UConstructionWidget::OnClickCornField);
	this->PumpkinField->OnClick.BindUObject(this, &UConstructionWidget::OnClickPumpkinField);
	this->LettuceField->OnClick.BindUObject(this, &UConstructionWidget::OnClickLettuceField);

	if (this->CropoutGameMode == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UPauseWidget::NativeOnInitialized(): CropoutGameMode == nullptr"));
		return;
	}
	FCardInformation CardInformation;
	CardInformation = this->CropoutGameMode->GetCardInformationFromTable(FName("Tree"));
	this->Tree->SetCardCost(CardInformation.CostMap);
    this->Tree->SetCardIcon(CardInformation.Icon);
    this->Tree->SetCardName(CardInformation.Name);
	CardInformation = this->CropoutGameMode->GetCardInformationFromTable(FName("Shrub"));
	this->Shrub->SetCardCost(CardInformation.CostMap);
	this->Shrub->SetCardIcon(CardInformation.Icon);
	this->Shrub->SetCardName(CardInformation.Name);
	CardInformation = this->CropoutGameMode->GetCardInformationFromTable(FName("VillagerHouse"));
	this->VillagerHouse->SetCardCost(CardInformation.CostMap);
	this->VillagerHouse->SetCardIcon(CardInformation.Icon);
	this->VillagerHouse->SetCardName(CardInformation.Name);
	CardInformation = this->CropoutGameMode->GetCardInformationFromTable(FName("Monument"));
	this->Monument->SetCardCost(CardInformation.CostMap);
	this->Monument->SetCardIcon(CardInformation.Icon);
	this->Monument->SetCardName(CardInformation.Name);
	CardInformation = this->CropoutGameMode->GetCardInformationFromTable(FName("CornField"));
	this->CornField->SetCardCost(CardInformation.CostMap);
    this->CornField->SetCardIcon(CardInformation.Icon);
    this->CornField->SetCardName(CardInformation.Name);
	CardInformation = this->CropoutGameMode->GetCardInformationFromTable(FName("WheatField"));
	this->WheatField->SetCardCost(CardInformation.CostMap);
	this->WheatField->SetCardIcon(CardInformation.Icon);
	this->WheatField->SetCardName(CardInformation.Name);
	CardInformation = this->CropoutGameMode->GetCardInformationFromTable(FName("PumpkinField"));
	this->PumpkinField->SetCardCost(CardInformation.CostMap);
	this->PumpkinField->SetCardIcon(CardInformation.Icon);
	this->PumpkinField->SetCardName(CardInformation.Name);
	CardInformation = this->CropoutGameMode->GetCardInformationFromTable(FName("LettuceField"));
	this->LettuceField->SetCardCost(CardInformation.CostMap);
	this->LettuceField->SetCardIcon(CardInformation.Icon);
	this->LettuceField->SetCardName(CardInformation.Name);

	GetWorld()->GetTimerManager().SetTimer(this->TickTimer, this, &UConstructionWidget::TickTimerFunction, 0.01f, true);
	GetWorld()->GetTimerManager().PauseTimer(this->TickTimer);
}


void UConstructionWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

}

void UConstructionWidget::NativeDestruct()
{
	Super::NativeDestruct();

}

void UConstructionWidget::TickTimerFunction()
{
	

}


void UConstructionWidget::InitializeAnimation(UWidgetAnimation* SelectionPanel, UWidgetAnimation* OperationPanel)
{
	this->CardSelectionPanelAnimation = SelectionPanel;
    this->CardOperationPanelAnimation = OperationPanel;
	if(CardSelectionPanelAnimation == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("CardSelectionPanelAnimation == nullptr"));
		return;
	}
    if(CardOperationPanelAnimation == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("CardOperationPanelAnimation == nullptr"));
		return;
	}
	
}

void UConstructionWidget::SetCardOperationPanelPosition(const FVector2D& NewPosition)
{
	FVector2D OffsetPosition;
	OffsetPosition.X = CardOperationPanel->GetWidthOverride() / -2.0f;
	OffsetPosition.Y = 100.0f;
    CardOperationPanel->SetRenderTranslation(NewPosition + OffsetPosition);



}


void UConstructionWidget::OpenCardSelectionPanel()
{
	this->CardSelectionPanel->SetVisibility(ESlateVisibility::Visible);
	PlayAnimation(CardSelectionPanelAnimation,0.0f,1,EUMGSequencePlayMode::Forward,4.0f);
}


void UConstructionWidget::CloseCardSelectionPanel()
{
	PlayAnimation(CardSelectionPanelAnimation, 0.0f, 1, EUMGSequencePlayMode::Reverse, 4.0f);
}

void UConstructionWidget::OpenCardOperationPanel()
{
	this->CardOperationPanel->SetVisibility(ESlateVisibility::Visible);
	this->CardSelectionPanel->SetVisibility(ESlateVisibility::HitTestInvisible);
	this->CardSelectionPanel->SetRenderOpacity(0.5f);
	PlayAnimation(CardOperationPanelAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward, 4.0f);
}


void UConstructionWidget::CloseCardOperationPanel()
{
	this->CardSelectionPanel->SetVisibility(ESlateVisibility::Visible);
	this->CardSelectionPanel->SetRenderOpacity(1.0f);
	PlayAnimation(CardOperationPanelAnimation, 0.0f, 1, EUMGSequencePlayMode::Reverse, 4.0f);
}


void UConstructionWidget::OnClickReturnButton()
{
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnPlayerCloseCardSelectionPanel.Broadcast();

}

void UConstructionWidget::OnClickPlacementButton()
{
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnPlayerPlaceGameObject.Broadcast(this->SelectedCardInformation);

}

void UConstructionWidget::OnClickRotationButton()
{
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnPlayerRotateGameObject.Broadcast();
}

void UConstructionWidget::OnClickCancelButton()
{
	CloseCardOperationPanel();
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnPlayerCloseCardOperationPanel.Broadcast();


}


void UConstructionWidget::OnClickCornField()
{
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnPlayerSelectCard.Broadcast(this->CornField->GetCardInformation());
	this->SelectedCardInformation = this->CornField->GetCardInformation();
	OpenCardOperationPanel();


}

void UConstructionWidget::OnClickWheatField()
{
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnPlayerSelectCard.Broadcast(this->WheatField->GetCardInformation());
	this->SelectedCardInformation = this->WheatField->GetCardInformation();
	OpenCardOperationPanel();


}

void UConstructionWidget::OnClickPumpkinField()
{
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnPlayerSelectCard.Broadcast(this->PumpkinField->GetCardInformation());
	this->SelectedCardInformation = this->PumpkinField->GetCardInformation();
	OpenCardOperationPanel();


}

void UConstructionWidget::OnClickLettuceField()
{
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnPlayerSelectCard.Broadcast(this->LettuceField->GetCardInformation());
	this->SelectedCardInformation = this->LettuceField->GetCardInformation();
	OpenCardOperationPanel();


}

void UConstructionWidget::OnClickTree()
{
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnPlayerSelectCard.Broadcast(this->Tree->GetCardInformation());
	this->SelectedCardInformation = this->Tree->GetCardInformation();
	OpenCardOperationPanel();


}


void UConstructionWidget::OnClickShrub()
{
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnPlayerSelectCard.Broadcast(this->Shrub->GetCardInformation());
	this->SelectedCardInformation = this->Shrub->GetCardInformation();
	OpenCardOperationPanel();

}


void UConstructionWidget::OnClickMonument()
{
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnPlayerSelectCard.Broadcast(this->Monument->GetCardInformation());
	this->SelectedCardInformation = this->Monument->GetCardInformation();
	OpenCardOperationPanel();

}


void UConstructionWidget::OnClickVillagerHouse()
{
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnPlayerSelectCard.Broadcast(this->VillagerHouse->GetCardInformation());
	this->SelectedCardInformation = this->VillagerHouse->GetCardInformation();
	OpenCardOperationPanel();

}



void UConstructionWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	Super::OnAnimationFinished_Implementation(Animation);
	if(Animation == this->CardOperationPanelAnimation && this->CardOperationPanel->GetRenderOpacity() == 0.0f)
	{
		this->CardOperationPanel->SetVisibility(ESlateVisibility::Hidden);

	}
	if (Animation == this->CardSelectionPanelAnimation && this->CardSelectionPanel->GetRenderOpacity() == 0.0f)
	{
		this->CardSelectionPanel->SetVisibility(ESlateVisibility::Hidden);
		this->CropoutGameMode->GetGameInstance()->GetWidgetManager()->RemoveTopWidgetFromViewport();


	}


}









