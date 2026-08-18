

#include "Manager/WidgetManager.h"
#include "UI/BackGroundWidget.h"
#include "UI/StartWidget.h"
#include "UI/UserTipWidget.h"
#include "UI/LoadWidget.h"
#include "UI/PauseWidget.h"
#include "Blueprint/GameViewportSubsystem.h"
#include "UI/BattleWidget.h"
#include "UI/ConstructionWidget.h"
#include "UI/TextBlockWidget.h"
#include "UI/ProgressBarWidget.h"
#include "UI/VictoryWidget.h"
#include "UI/FailureWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"



void UWidgetManager::CreateCropoutWidget( UGameInstance* GameInstance, TMap<EWidgetType, UClass*> WidgetClassMap)
{
	if (WidgetClassMap.Find(EWidgetType::Start) == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UWidgetManager::CreateCropoutWidget(): WidgetClassMap.Find(EWidgetType::Start) == nullptr"));
		return;
	}
	if (WidgetClassMap.Find(EWidgetType::BackGround) == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UWidgetManager::CreateCropoutWidget(): WidgetClassMap.Find(EWidgetType::BackGround) == nullptr"));
		return;
	}
	if (WidgetClassMap.Find(EWidgetType::UserTip) == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UWidgetManager::CreateCropoutWidget(): WidgetClassMap.Find(EWidgetType::UserTip) == nullptr"));
		return;
	}
	if (WidgetClassMap.Find(EWidgetType::Load) == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UWidgetManager::CreateCropoutWidget(): WidgetClassMap.Find(EWidgetType::Load) == nullptr"));
		return;
	}
	if (WidgetClassMap.Find(EWidgetType::Pause) == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UWidgetManager::CreateCropoutWidget(): WidgetClassMap.Find(EWidgetType::Pause) == nullptr"));
		return;
	}
	if (WidgetClassMap.Find(EWidgetType::Battle) == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UWidgetManager::CreateCropoutWidget(): WidgetClassMap.Find(EWidgetType::Battle) == nullptr"));
		return;
	}
	if (WidgetClassMap.Find(EWidgetType::Construction) == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UWidgetManager::CreateCropoutWidget(): WidgetClassMap.Find(EWidgetType::Construction) == nullptr"));
		return;
	}
	this->VictoryWidget = CreateWidget<UVictoryWidget>(GameInstance, *WidgetClassMap.Find(EWidgetType::Victory));
	this->FailureWidget = CreateWidget<UFailureWidget>(GameInstance, *WidgetClassMap.Find(EWidgetType::Failure));
	this->StartWidget = CreateWidget<UStartWidget>(GameInstance, *WidgetClassMap.Find(EWidgetType::Start));
	this->BackGroundWidget = CreateWidget<UBackGroundWidget>(GameInstance, *WidgetClassMap.Find(EWidgetType::BackGround));
	this->UserTipWidget = CreateWidget<UUserTipWidget>(GameInstance, *WidgetClassMap.Find(EWidgetType::UserTip));
	this->LoadWidget = CreateWidget<ULoadWidget>(GameInstance, *WidgetClassMap.Find(EWidgetType::Load));
	this->PauseWidget = CreateWidget<UPauseWidget>(GameInstance, *WidgetClassMap.Find(EWidgetType::Pause));
	this->BattleWidget = CreateWidget<UBattleWidget>(GameInstance, *WidgetClassMap.Find(EWidgetType::Battle));
	this->ConstructionWidget = CreateWidget<UConstructionWidget>(GameInstance, *WidgetClassMap.Find(EWidgetType::Construction));
}


void UWidgetManager::AddFailureWidgetToViewport()
{
	if (this->ActiveWidgetArray.Contains(this->FailureWidget))
	{
		UE_LOG(LogTemp, Warning, TEXT("UWidgetManager::AddFailureWidgetToViewport(): this->ActiveWidgetArray.Contains(this->StartWidget)"));
		return;
	}
	this->FailureWidget->AddToViewport();
	this->ActiveWidgetArray.AddUnique(this->FailureWidget);
	UpdateBackGroundIamge(EWidgetType::Failure);
	//UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx();

}

void UWidgetManager::AddVictoryWidgetToViewport()
{
	if (this->ActiveWidgetArray.Contains(this->VictoryWidget))
	{
		UE_LOG(LogTemp, Warning, TEXT("UWidgetManager::AddVictoryWidgetToViewport(): this->ActiveWidgetArray.Contains(this->StartWidget)"));
		return;
	}
	this->VictoryWidget->AddToViewport();
	this->ActiveWidgetArray.AddUnique(this->VictoryWidget);
	UpdateBackGroundIamge(EWidgetType::Victory);

}

void UWidgetManager::AddResourceTipToViewport()
{
	this->UserTipWidget->DisplayResourceTip();
}

void UWidgetManager::AddPlacementTipToViewport()
{
	this->UserTipWidget->DisplayPlacementTip();
}

void UWidgetManager::AddSaveGameTipToViewport()
{
	this->UserTipWidget->DisplaySaveGameTip();

}


void UWidgetManager::AddObjectCountTipToViewport()
{
	this->UserTipWidget->DisplayObjectCountTip();

}



void UWidgetManager::UpdateCardOperationPanelPosition(const FVector2D& NewPosition)
{
	this->ConstructionWidget->SetCardOperationPanelPosition(NewPosition);

}


void UWidgetManager::OpenCardSelectionPanel()
{
	//AddConstructionWidgetInViewport();
	this->ConstructionWidget->OpenCardSelectionPanel();
	this->BattleWidget->HideConstructionButton();
	this->BattleWidget->HidePauseButton();
}

void UWidgetManager::CloseCardSelectionPanel()
{
	this->ConstructionWidget->CloseCardSelectionPanel();
	this->BattleWidget->DisplayConstructionButton();
	this->BattleWidget->DisplayPauseButton();
	//RemoveTopWidgetFromViewport();

}

void UWidgetManager::OpenCardOperationPanel()
{

}

void UWidgetManager::CloseCardOperationPanel()
{


}


void UWidgetManager::UpdateBackGroundIamge(EWidgetType Widget)
{
	this->BackGroundWidget->SetBackGroundImage(Widget);
}


void UWidgetManager::PlayLoadAnimation(EUMGSequencePlayMode::Type PlayMode, float PlayRate)
{
	this->LoadWidget->PlayLoadAnimation(PlayMode, PlayRate);
}

void UWidgetManager::RemoveAllWidgetFromViewport()
{
	if (this->ActiveWidgetArray.Num() == 0)
	{
		return;
	}
	for (auto& Element : this->ActiveWidgetArray)
	{
		if(Element!=nullptr)
		{
			Element->RemoveFromParent();
			//this->ActiveWidgetArray.Remove(Element);
		}
	}
	this->ActiveWidgetArray.Reset();
	//UE_LOG(LogTemp, Warning, TEXT("Number= %d"),this->ActiveWidgetArray.Num());
}

void UWidgetManager::RemoveTopWidgetFromViewport()
{
	if(this->ActiveWidgetArray.Num()==0)
	{
		return;
	}
	int32 TopIndex = this->ActiveWidgetArray.Num() - 1;
	this->ActiveWidgetArray[TopIndex]->RemoveFromParent();
	this->ActiveWidgetArray.RemoveAt(TopIndex);

}


void UWidgetManager::AddStartWidgetToViewport()
{
	if(this->ActiveWidgetArray.Contains(this->StartWidget))
	{
		UE_LOG(LogTemp,Warning, TEXT("UWidgetManager::AddStartWidgetToViewport(): this->ActiveWidgetArray.Contains(this->StartWidget)"));
		return;
	}
	this->StartWidget->AddToViewport();
	this->ActiveWidgetArray.AddUnique(this->StartWidget);
	UpdateBackGroundIamge(EWidgetType::Start);

}


void UWidgetManager::AddConstructionWidgetInViewport()
{
	if (this->ActiveWidgetArray.Contains(this->ConstructionWidget))
	{
		UE_LOG(LogTemp, Warning, TEXT("UWidgetManager::AddConstructionWidgetInViewport(): this->ActiveWidgetArray.Contains(this->ConstructionWidget)"));
		return;
	}
	this->ConstructionWidget->AddToViewport();
	this->ActiveWidgetArray.AddUnique(this->ConstructionWidget);
	//UpdateBackGroundIamge(EWidgetType::None);

}


void UWidgetManager::AddPauseWidgetToViewport()
{
	if (this->ActiveWidgetArray.Contains(this->PauseWidget))
	{
		UE_LOG(LogTemp, Warning, TEXT(" UWidgetManager::AddPauseWidgetToViewport(): this->ActiveWidgetArray.Contains(this->PauseWidget)"));
		return;
	}
	this->PauseWidget->AddToViewport();
	this->ActiveWidgetArray.AddUnique(this->PauseWidget);
	UpdateBackGroundIamge(EWidgetType::Pause);

}


void UWidgetManager::AddBattleWidgetToViewport()
{
	if (this->ActiveWidgetArray.Contains(this->BattleWidget))
	{
		UE_LOG(LogTemp, Warning, TEXT(" UWidgetManager::AddBattleWidgetToViewport(): this->ActiveWidgetArray.Contains(this->BattleWidget)"));
		return;
	}
	this->BattleWidget->AddToViewport();
	this->ActiveWidgetArray.AddUnique(this->BattleWidget);
	UpdateBackGroundIamge(EWidgetType::None);

}


void UWidgetManager::AddBackGroundWidgetToViewport()
{
	this->BackGroundWidget->AddToViewport(-1);
}

void UWidgetManager::RemoveBackGroundWidgetFromViewport()
{
    this->BackGroundWidget->RemoveFromParent();
}

void UWidgetManager::AddUserTipWidgetYoViewport()
{
	this->UserTipWidget->AddToViewport(100);
}

void UWidgetManager::RemoveUserTipWidgetFromViewport()
{
    this->UserTipWidget->RemoveFromParent();
}

void UWidgetManager::AddLoadWidgetToViewport()
{
	this->LoadWidget->AddToViewport(101);
}

void UWidgetManager::RemoveLoadWidgetFromViewport()
{
	this->LoadWidget->RemoveFromParent();
}


void UWidgetManager::BindDamageText(UGameInstance* GameInstance,UClass* TextBlockWidgetClass,FName ActorName )
{
	UTextBlockWidget* DamageText = nullptr;
	DamageText = CreateWidget<UTextBlockWidget>(GameInstance, TextBlockWidgetClass);
	if (DamageText == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UWidgetManager::BindDamageText(): DamageText == nullptr"));
		return;
	}
	this->DamageTextMap.Add(ActorName, DamageText);
	this->UserTipWidget->AddWidgetToCanvasPanel(DamageText);
	DamageText->IsShowBackGroundImage = false;
	DamageText->SetVisibility(ESlateVisibility::Hidden);
	DamageText->SetFontInformation(40.0f);
	DamageText->SetSize(200.0f,50.0f);
	
	///UE_LOG(LogTemp, Warning, TEXT("BindDamageText: this->DamageTextMap.Num() = %d"),this->DamageTextMap.Num());



}


void UWidgetManager::UnbindDamageText(FName ActorName)
{
	UTextBlockWidget* DamageText = nullptr;
	if (this->DamageTextMap.Find(ActorName) == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UWidgetManager::UnbindDamageText(): this->DamageTextMap.Find(ActorName) == nullptr"));
		return;
	}
	DamageText = *this->DamageTextMap.Find(ActorName);
	if(DamageText->GetVisibility() != ESlateVisibility::Hidden)
	{
		DamageText->SetVisibility(ESlateVisibility::Hidden);
	}
	this->UserTipWidget->RemoveWidgetFromCanvasPanel(DamageText);
	this->DamageTextMap.Remove(ActorName);
	//UE_LOG(LogTemp, Warning, TEXT("UnbindDamageText: this->DamageTextMap.Num() = %d !!!"), this->DamageTextMap.Num());



}

void UWidgetManager::DisplayDamageText(FName ActorName, float Damage)
{
	UTextBlockWidget* DamageText = nullptr;
	if (this->DamageTextMap.Find(ActorName) == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UWidgetManager::DisplayDamageText(): this->DamageTextMap.Find(ActorName) == nullptr"));
		return;
	}
	DamageText = *this->DamageTextMap.Find(ActorName);
	if (DamageText->GetVisibility() == ESlateVisibility::Hidden)
	{
		DamageText->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	DamageText->SetText(FText::FromString(FString::FromInt(int32(Damage))));
	DamageText->PlayDamageTextAnimation(1.0f);


}


void UWidgetManager::UpdateDamageTextPosition(FName ActorName, const FVector2D& Position)
{
	UTextBlockWidget* DamageText = nullptr;
	FVector2D OffsetPosition = FVector2D(0.0f, 0.0f);
	if (this->DamageTextMap.Find(ActorName) == nullptr)
	{
		//UE_LOG(LogTemp, Error, TEXT("UWidgetManager::UpdateDamageTextPosition(): this->DamageTextMap.Find(ActorName) == nullptr"));
		return;
	}
	DamageText = *this->DamageTextMap.Find(ActorName);
	if(DamageText->GetTextBlockRenderOpacity() == 0.0f)
	{
		OffsetPosition.X = -DamageText->GetWidth() / 2.0f + FMath::RandRange(-50.0f, 50.0f);
		OffsetPosition.Y = -100.0f + FMath::RandRange(-50.0f, 50.0f);
	}
	OffsetPosition.X = -DamageText->GetWidth() / 2.0f ;
	OffsetPosition.Y = -100.0f ;
	DamageText->SetRenderTranslation(Position + OffsetPosition);


}


void UWidgetManager::BindHealthBar(UGameInstance* GameInstance, UClass* HealthBarWidgetClass, FName ActorName)
{
	UProgressBarWidget* HealthBar = nullptr;
	FColor BackGroundImageColor = FColor::Black;
	FColor FillImageColor = FColor(0.02f, 0.5f, 0.0f, 1.0f);
	HealthBar = CreateWidget<UProgressBarWidget>(GameInstance, HealthBarWidgetClass);
	if(HealthBar==nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UWidgetManager::BindHealthBar(): HealthBar==nullptr"));
		return;
	}
	this->HealthBarMap.Add(ActorName, HealthBar);
	this->UserTipWidget->AddWidgetToCanvasPanel(HealthBar);
	HealthBar->IsShowText = false;
	HealthBar->SetSize(100.0f, 20.0f);
	HealthBar->SetBackGroundImageStyle(ESlateBrushDrawType::RoundedBox, ESlateBrushRoundingType::FixedRadius, FVector4(10.0f), 0.0f, BackGroundImageColor);
    HealthBar->SetFillImageStyle(ESlateBrushDrawType::RoundedBox, ESlateBrushRoundingType::FixedRadius, FVector4(10.0f), 3.0f, FillImageColor);
	HealthBar->SetVisibility(ESlateVisibility::Hidden);



}



void UWidgetManager::UnbindHealthBar(FName ActorName)
{
	UProgressBarWidget* HealthBar = nullptr;
	if (this->HealthBarMap.Find(ActorName) == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UWidgetManager::DisplayHealthBar(): this->HealthBarMap.Find(ActorName) == nullptr"));
		return;
	}
	HealthBar = *this->HealthBarMap.Find(ActorName);
	if (HealthBar->GetVisibility() != ESlateVisibility::Hidden)
	{
		HealthBar->SetVisibility(ESlateVisibility::Hidden);
	}
	this->UserTipWidget->RemoveWidgetFromCanvasPanel(HealthBar);
	this->HealthBarMap.Remove(ActorName);


}

void UWidgetManager::DisplayHealthBar(FName ActorName, float HealthPercent)
{
	UProgressBarWidget* HealthBar = nullptr;
	if (this->HealthBarMap.Find(ActorName) == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UWidgetManager::DisplayHealthBar(): this->HealthBarMap.Find(ActorName) == nullptr"));
		return;
	}
	HealthBar = *this->HealthBarMap.Find(ActorName);
	if (HealthBar->GetSizeBoxRenderOpacity() == 0.0f)
	{
		HealthBar->PlayFadeInAnimation(1.0f);
	}
	if(HealthBar->GetVisibility() == ESlateVisibility::Hidden)
	{
		HealthBar->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
	HealthBar->SetPercent(HealthPercent);
	if(HealthPercent <= 0.0f || HealthPercent >= 1.0f)
	{
		HealthBar->PlayFadeOutAnimation(1.0f);
	}


}


void UWidgetManager::UpdateHealthBarPosition(FName ActorName, const FVector2D& Position)
{
	UProgressBarWidget* HealthBar = nullptr;
	FVector2D OffsetPosition = FVector2D(0.0f, 0.0f);
	if (this->HealthBarMap.Find(ActorName) == nullptr)
	{
		//UE_LOG(LogTemp, Error, TEXT("UWidgetManager::UpdateHealthBarPosition(): this->HealthBarMap.Find(ActorName) == nullptr"));
		return;
	}
	HealthBar = *this->HealthBarMap.Find(ActorName);
	OffsetPosition = FVector2D(HealthBar->GetWidth() * 0.5f, 0.0f);
	HealthBar->SetRenderTranslation(Position - OffsetPosition);


}

