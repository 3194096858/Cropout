
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseWidget.generated.h"





class UButtonWidget;

class ACropoutGameMode;
class UWidgetAnimation;
class USliderWidget;


UCLASS()
class CROPOUT_API UPauseWidget : public UUserWidget
{
	GENERATED_BODY()

private:
    virtual void NativeConstruct() override;
    virtual void NativePreConstruct() override;
    virtual void NativeDestruct() override;
    virtual void NativeOnInitialized() override;
public:

protected:
    UPROPERTY()
    ACropoutGameMode* CropoutGameMode;
private:
    UPROPERTY(meta = (BindWidget))
    UButtonWidget* ResumeButton;
    UPROPERTY(meta = (BindWidget))
    UButtonWidget* RestartButton;
    UPROPERTY(meta = (BindWidget))
    UButtonWidget* QuitButton;
    UPROPERTY(meta = (BindWidget))
    UButtonWidget* SaveButton;
    UPROPERTY(meta = (BindWidget))
    USliderWidget* BGMSlider;
    UPROPERTY(meta = (BindWidget))
    USliderWidget* SFXSlider;
    UPROPERTY()
    UWidgetAnimation* FadeInAnimation;
    
public:
    UFUNCTION(BlueprintCallable)
    void InitializeAnimation(UWidgetAnimation* FadeIn);

private:
    UFUNCTION()
    void CloseGamePausePanel();
    UFUNCTION()
    void OpenGamePausePanel();
    UFUNCTION()
    void OnClickResumeButton();
    UFUNCTION()
    void OnClickRestartButton();
    UFUNCTION()
    void OnClickQuitButton();
    UFUNCTION()
    void OnClickSaveButton();
    UFUNCTION()
    void OnBGMSliderValueChange(float Value);
    UFUNCTION()
    void OnSFXSliderValueChange(float Value);

};
