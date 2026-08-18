
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VictoryWidget.generated.h"



class UButtonWidget;
class UTextBlockWidget;
class ACropoutGameMode;
class UWidgetAnimation;

UCLASS()
class CROPOUT_API UVictoryWidget : public UUserWidget
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
public:
    UPROPERTY(meta = (BindWidget))
    UButtonWidget* ResumeButton;
    UPROPERTY(meta = (BindWidget))
    UButtonWidget* RestartButton;
    UPROPERTY(meta = (BindWidget))
    UButtonWidget* QuitButton;
    UPROPERTY(meta = (BindWidget))
    UTextBlockWidget* PlayTime;
private:
    UPROPERTY()
    UWidgetAnimation* FadeInAnimation;

public:
    UFUNCTION(BlueprintCallable)
    void InitializeAnimation(UWidgetAnimation* FadeIn);

private:
    UFUNCTION()
    void CloseVictoryPanel();
    UFUNCTION()
    void OpenVictoryPanel();
    UFUNCTION()
    void OnClickResumeButton();
    UFUNCTION()
    void OnClickRestartButton();
    UFUNCTION()
    void OnClickQuitButton();
   
};
