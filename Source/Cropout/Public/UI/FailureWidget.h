
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FailureWidget.generated.h"



class UButtonWidget;

class ACropoutGameMode;
class UWidgetAnimation;


UCLASS()
class CROPOUT_API UFailureWidget : public UUserWidget
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
    UButtonWidget* RestartButton;
    UPROPERTY(meta = (BindWidget))
    UButtonWidget* QuitButton;


private:
    UPROPERTY()
    UWidgetAnimation* FadeInAnimation;

public:
    UFUNCTION(BlueprintCallable)
    void InitializeAnimation(UWidgetAnimation* FadeIn);

private:
    UFUNCTION()
    void CloseFailurePanel();
    UFUNCTION()
    void OpenFailurePanel();
    UFUNCTION()
    void OnClickRestartButton();
    UFUNCTION()
    void OnClickQuitButton();






};
