

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BattleWidget.generated.h"



class UButtonWidget;
class UTextBlockWidget;
class ACropoutGameMode;
class UWidgetAnimation;



UCLASS()
class CROPOUT_API UBattleWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeOnInitialized() override;
public:
	UPROPERTY(meta = (BindWidget))
	UButtonWidget* PauseButton;
	UPROPERTY(meta = (BindWidget))
	UButtonWidget* ConstructionButton;
	UPROPERTY(meta = (BindWidget))
	UTextBlockWidget* Wood;
	UPROPERTY(meta = (BindWidget))
	UTextBlockWidget* Food;
	UPROPERTY(meta = (BindWidget))
	UTextBlockWidget* Stone;
	UPROPERTY(meta = (BindWidget))
	UTextBlockWidget* Villager;


protected:
	UPROPERTY()
	ACropoutGameMode* CropoutGameMode;

private:
	UWidgetAnimation* FadeInAniamtion_ConstructionButton;
	UWidgetAnimation* FadeInAniamtion_PauseButton;
	UWidgetAnimation* FoodIncreaseAnimation;
	UWidgetAnimation* WoodIncreaseAnimation;
	UWidgetAnimation* StoneIncreaseAnimation;
	UWidgetAnimation* VillagerIncreaseAnimation;
	UWidgetAnimation* FoodReductionAnimation;
	UWidgetAnimation* WoodReductionAnimation;
	UWidgetAnimation* StoneReductionAnimation;

public:
	UFUNCTION(BlueprintCallable)
	void InitializeAnimation(UWidgetAnimation* FadeIn_ConstructionButton, UWidgetAnimation* FadeIn_PauseButton, UWidgetAnimation* Animation_FoodIncrease, UWidgetAnimation* Animation_WoodIncrease, UWidgetAnimation* Animation_StoneIncrease, UWidgetAnimation* Animation_VillagerIncrease, UWidgetAnimation* Animation_FoodReduction, UWidgetAnimation* Animation_WoodReduction, UWidgetAnimation* Animation_StoneReduction);
	UFUNCTION()
	void HideConstructionButton();
    UFUNCTION()
    void DisplayConstructionButton();
    UFUNCTION()
	void HidePauseButton();
    UFUNCTION()
    void DisplayPauseButton();
private:
	
	UFUNCTION()
	void OnClickConstructionButton();
	UFUNCTION()
	void OnClickPauseButton();
	UFUNCTION()
	void OnGameStart();
	UFUNCTION()
	void OnPlayerResourceIncrease(TMap<EResourceType,int32> ResourceMap);
	UFUNCTION()
	void OnPlayerResourceReduce(TMap<EResourceType, int32> ResourceMap);
	UFUNCTION()
	void OnVillagerCountIncrease(int32 Other);


};
