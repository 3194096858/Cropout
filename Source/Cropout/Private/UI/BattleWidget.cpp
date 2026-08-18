

#include "UI/BattleWidget.h"



#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "UI/ButtonWidget.h"
#include "UI/TextBlockWidget.h"

#include "GameMode/CropoutGameMode.h"
#include "GameInstance/CropoutGameInstance.h"
#include "Manager/DelegateManager.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/WidgetManager.h"
#include "Manager/DataManager.h"


void UBattleWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	this->ConstructionButton->OnClick.BindUObject(this, &UBattleWidget::OnClickConstructionButton);
	this->PauseButton->OnClick.BindUObject(this, &UBattleWidget::OnClickPauseButton);
	this->CropoutGameMode = Cast<ACropoutGameMode>(UGameplayStatics::GetGameMode(this));
	if (this->CropoutGameMode == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UPauseWidget::NativeOnInitialized(): CropoutGameMode == nullptr"));
		return;
	}
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnVillagerCountIncrease.AddUObject(this, &UBattleWidget::OnVillagerCountIncrease);
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnPlayerResourceReduce.AddUObject(this, &UBattleWidget::OnPlayerResourceReduce);
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnPlayerResourceIncrease.AddUObject(this, &UBattleWidget::OnPlayerResourceIncrease);
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameStart.AddUObject(this, &UBattleWidget::OnGameStart);
	
}


void UBattleWidget::NativeConstruct()
{
	Super::NativeConstruct();
	TMap<EResourceType, int32> PlayerResourceMap = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetPlayerData().ResourceMap;
	if (PlayerResourceMap.Find(EResourceType::Wood) == nullptr|| PlayerResourceMap.Find(EResourceType::Food) == nullptr|| PlayerResourceMap.Find(EResourceType::Stone) == nullptr)
	{
		return;
	}
	Wood->SetText(*PlayerResourceMap.Find(EResourceType::Wood));
	Food->SetText(*PlayerResourceMap.Find(EResourceType::Food));
	Stone->SetText(*PlayerResourceMap.Find(EResourceType::Stone));
	int32 VillagerCount = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetVillagerCount();
	Villager->SetText(VillagerCount);

}


void UBattleWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

}

void UBattleWidget::NativeDestruct()
{
	Super::NativeDestruct();

}

void UBattleWidget::InitializeAnimation(UWidgetAnimation* FadeIn_ConstructionButton, UWidgetAnimation* FadeIn_PauseButton, UWidgetAnimation* Animation_FoodIncrease, UWidgetAnimation* Animation_WoodIncrease, UWidgetAnimation* Animation_StoneIncrease, UWidgetAnimation* Animation_VillagerIncrease, UWidgetAnimation* Animation_FoodReduction, UWidgetAnimation* Animation_WoodReduction, UWidgetAnimation* Animation_StoneReduction)
{
	this->FadeInAniamtion_ConstructionButton = FadeIn_ConstructionButton;
    this->FadeInAniamtion_PauseButton = FadeIn_PauseButton;
	this->FoodIncreaseAnimation = Animation_FoodIncrease;
	this->WoodIncreaseAnimation = Animation_WoodIncrease;
	this->StoneIncreaseAnimation = Animation_StoneIncrease;
	this->VillagerIncreaseAnimation = Animation_VillagerIncrease;
	this->FoodReductionAnimation = Animation_FoodReduction;
	this->WoodReductionAnimation = Animation_WoodReduction;
	this->StoneReductionAnimation = Animation_StoneReduction;

	if (this->FadeInAniamtion_ConstructionButton == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT(" UBattleWidget::InitializeAnimation(): FadeInAniamtion_ConstructionButton == nullptr"));
	}
	if(this->FadeInAniamtion_PauseButton == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT(" UBattleWidget::InitializeAnimation(): FadeInAniamtion_PauseButton == nullptr"));
	}
	if(this->StoneReductionAnimation == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT(" UBattleWidget::InitializeAnimation(): StoneReduction_Animation == nullptr"));
	}
	if (this->FoodReductionAnimation == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT(" UBattleWidget::InitializeAnimation(): FoodReduction_Animation == nullptr"));
	}
	if (this->WoodReductionAnimation == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT(" UBattleWidget::InitializeAnimation(): WoodReduction_Animation == nullptr"));
	}
	if (this->StoneIncreaseAnimation == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT(" UBattleWidget::InitializeAnimation(): StoneReduction_Animation == nullptr"));
	}
	if (this->FoodIncreaseAnimation == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT(" UBattleWidget::InitializeAnimation(): FoodReduction_Animation == nullptr"));
	}
	if (this->WoodIncreaseAnimation == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT(" UBattleWidget::InitializeAnimation(): WoodReduction_Animation == nullptr"));
	}
	if (this->VillagerIncreaseAnimation == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT(" UBattleWidget::InitializeAnimation(): WoodReduction_Animation == nullptr"));
	}
}

void UBattleWidget::OnClickConstructionButton()
{
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnPlayerOpenCardSelectionPanel.Broadcast();

}


void UBattleWidget::OnClickPauseButton()
{
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGamePause.Broadcast();
	this->CropoutGameMode->GetGameInstance()->GetDataManager()->SetGameStatus(EGameStatus::GamePause);

}


void UBattleWidget::OnGameStart()
{
}



void UBattleWidget::DisplayPauseButton()
{
	PlayAnimation(this->FadeInAniamtion_PauseButton, 0.0f,1,EUMGSequencePlayMode::Type::Forward, 5.0f);
}

void UBattleWidget::HidePauseButton()
{
	PlayAnimation(this->FadeInAniamtion_PauseButton,0.0f,1, EUMGSequencePlayMode::Type::Reverse, 5.0f);
}

void UBattleWidget::DisplayConstructionButton()
{
	PlayAnimation(this->FadeInAniamtion_ConstructionButton,0.0f,1, EUMGSequencePlayMode::Type::Forward, 5.0f);

}


void UBattleWidget::HideConstructionButton()
{
	PlayAnimation(this->FadeInAniamtion_ConstructionButton, 0.0f,1,EUMGSequencePlayMode::Type::Reverse, 5.0f);


}



void UBattleWidget::OnPlayerResourceIncrease(TMap<EResourceType, int32> OtherResource)
{
	TMap<EResourceType, int32> PlayerResourceMap = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetPlayerData().ResourceMap;
	if (PlayerResourceMap.Find(EResourceType::Wood) == nullptr || PlayerResourceMap.Find(EResourceType::Food) == nullptr || PlayerResourceMap.Find(EResourceType::Stone) == nullptr)
	{
		return;
	}
	Wood->SetText(*PlayerResourceMap.Find(EResourceType::Wood));
	Food->SetText(*PlayerResourceMap.Find(EResourceType::Food));
	Stone->SetText(*PlayerResourceMap.Find(EResourceType::Stone));
	if(*OtherResource.Find(EResourceType::Wood) != 0)
	{
		PlayAnimation(this->WoodIncreaseAnimation, 0.0f, 1, EUMGSequencePlayMode::Type::Forward, 2.0f);
	}

	if(*OtherResource.Find(EResourceType::Food) != 0)
	{
        PlayAnimation(this->FoodIncreaseAnimation, 0.0f, 1, EUMGSequencePlayMode::Type::Forward, 2.0f);
	}

	if (*OtherResource.Find(EResourceType::Stone) != 0)
	{
		PlayAnimation(this->StoneIncreaseAnimation, 0.0f, 1, EUMGSequencePlayMode::Type::Forward, 2.0f);
	}



}

void UBattleWidget::OnPlayerResourceReduce(TMap<EResourceType, int32> OtherResource)
{
	TMap<EResourceType, int32> PlayerResourceMap = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetPlayerData().ResourceMap;
	if (PlayerResourceMap.Find(EResourceType::Wood) == nullptr || PlayerResourceMap.Find(EResourceType::Food) == nullptr || PlayerResourceMap.Find(EResourceType::Stone) == nullptr)
	{
		return;
	}
	Wood->SetText(*PlayerResourceMap.Find(EResourceType::Wood));
	Food->SetText(*PlayerResourceMap.Find(EResourceType::Food));
	Stone->SetText(*PlayerResourceMap.Find(EResourceType::Stone));
	if (*OtherResource.Find(EResourceType::Wood) != 0)
	{
		PlayAnimation(this->WoodReductionAnimation, 0.0f, 1, EUMGSequencePlayMode::Type::Forward, 2.0f);

	}
	if (*OtherResource.Find(EResourceType::Food) != 0)
	{
		PlayAnimation(this->FoodReductionAnimation, 0.0f, 1, EUMGSequencePlayMode::Type::Forward, 2.0f);
	}
	if (*OtherResource.Find(EResourceType::Stone) != 0)
	{
		PlayAnimation(this->StoneReductionAnimation, 0.0f, 1, EUMGSequencePlayMode::Type::Forward, 2.0f);
	}

}


void UBattleWidget::OnVillagerCountIncrease(int32 Other)
{
	int32 VillagerCount = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetVillagerCount();
	Villager->SetText(VillagerCount);
	
	PlayAnimation(this->VillagerIncreaseAnimation, 0.0f, 1, EUMGSequencePlayMode::Type::Forward, 2.0f);

	
	

}