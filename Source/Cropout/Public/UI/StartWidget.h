
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartWidget.generated.h"

class UButtonWidget;
class USizeBox;
class ACropoutGameMode;
class UWidgetAnimation;


UCLASS()
class CROPOUT_API UStartWidget : public UUserWidget
{
	GENERATED_BODY()
public:
    //UStartWidget();
private:
    virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeOnInitialized() override;
    virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;
public:

protected:
    UPROPERTY()
    ACropoutGameMode* CropoutGameMode;
private:
    UPROPERTY(meta = (BindWidget))
    USizeBox* StartPanel;
    UPROPERTY(meta = (BindWidget))
    USizeBox* SaveGameWarningPanel;
	UPROPERTY(meta = (BindWidget))
	UButtonWidget* ContinuationButton;
	UPROPERTY(meta = (BindWidget))
    UButtonWidget* NewGameButton;
    UPROPERTY(meta = (BindWidget))
    UButtonWidget* QuitButton;
    UPROPERTY(meta = (BindWidget))
    UButtonWidget* ConfirmedButton;
    UPROPERTY(meta = (BindWidget))
    UButtonWidget* ReturnButton;
    UPROPERTY()
    UWidgetAnimation* StartPanelAnimation;
    UPROPERTY()
    UWidgetAnimation* SaveGameWarningPanelAnimation;
    FTimerHandle DelayTimer;
public:
    UFUNCTION(BlueprintCallable)
    void InitializeAnimation(UWidgetAnimation* Animation_StartPanel, UWidgetAnimation* Animation_SaveGameWarningPanel);

private:
    UFUNCTION()
    void OpenStartPanel();
    UFUNCTION()
    void OpenSaveGameWarningPanel();
    UFUNCTION()
    void CloseStartPanel();
    UFUNCTION()
    void CloseSaveGameWarningPanel();
    UFUNCTION()
    void OnClickContinuationButton();
    UFUNCTION()
    void OnClickNewGameButton();
    UFUNCTION()
    void OnClickQuitButton();
    UFUNCTION()
    void OnClickConfirmedButton();
    UFUNCTION()
    void OnClickReturnButton();
 
};
