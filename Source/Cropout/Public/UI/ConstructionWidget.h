
#pragma once

#include "Struct/CardInformation.h"



#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ConstructionWidget.generated.h"

class UButtonWidget;
class UCardWidget;
class ACropoutGameMode;
class UWidgetAnimation;
class USizeBox;

UCLASS()
class CROPOUT_API UConstructionWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	virtual void NativePreConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeOnInitialized() override;
	virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;
public:
	UPROPERTY(meta = (BindWidget))
	USizeBox* CardSelectionPanel;
	UPROPERTY(meta = (BindWidget))
	USizeBox* CardOperationPanel;
	UPROPERTY(meta = (BindWidget))
	UButtonWidget* ReturnButton;
	UPROPERTY(meta = (BindWidget))
	UCardWidget* Tree;
	UPROPERTY(meta = (BindWidget))
	UCardWidget* Shrub;
	UPROPERTY(meta = (BindWidget))
	UCardWidget* Monument;
	UPROPERTY(meta = (BindWidget))
	UCardWidget* VillagerHouse;
	UPROPERTY(meta = (BindWidget))
	UCardWidget* CornField;
	UPROPERTY(meta = (BindWidget))
	UCardWidget* WheatField;
	UPROPERTY(meta = (BindWidget))
	UCardWidget* PumpkinField;
	UPROPERTY(meta = (BindWidget))
	UCardWidget* LettuceField;
	UPROPERTY(meta = (BindWidget))
	UButtonWidget* PlacementButton;
	UPROPERTY(meta = (BindWidget))
	UButtonWidget* RotationButton;
	UPROPERTY(meta = (BindWidget))
	UButtonWidget* CancelButton;
	
protected:
	UPROPERTY()
	ACropoutGameMode* CropoutGameMode;

private:
	UWidgetAnimation* CardOperationPanelAnimation;
	UWidgetAnimation* CardSelectionPanelAnimation;
	FCardInformation SelectedCardInformation;
	FTimerHandle TickTimer;
public:
	UFUNCTION()
	void TickTimerFunction();
	UFUNCTION()
	void SetCardOperationPanelPosition(const FVector2D& NewPosition );
	UFUNCTION(BlueprintCallable)
	void InitializeAnimation(UWidgetAnimation* SelectionPanel, UWidgetAnimation* OperationPanel);
	UFUNCTION()
	void OpenCardSelectionPanel();
	UFUNCTION()
	void CloseCardSelectionPanel();
	UFUNCTION()
	void OpenCardOperationPanel();
	UFUNCTION()
	void CloseCardOperationPanel();
private:
	UFUNCTION()
	void OnClickCornField();
	UFUNCTION()
	void OnClickWheatField();
	UFUNCTION()
	void OnClickPumpkinField();
	UFUNCTION()
	void OnClickLettuceField();
	UFUNCTION()
	void OnClickTree();
	UFUNCTION()
	void OnClickShrub();
	UFUNCTION()
	void OnClickMonument();
	UFUNCTION()
	void OnClickVillagerHouse();
	UFUNCTION()
	void OnClickReturnButton();
	UFUNCTION()
	void OnClickPlacementButton();
	UFUNCTION()
	void OnClickRotationButton();
	UFUNCTION()
	void OnClickCancelButton();


};
