
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoadWidget.generated.h"



class ACropoutGameMode;
class UWidgetAnimation;
class UTexture2D;
class UImage;
class UCircularThrobber;

UCLASS()
class CROPOUT_API ULoadWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	virtual void NativePreConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeOnInitialized() override;
	virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;

public:
	UPROPERTY(meta = (BindWidget))
	UImage* BackGroundImage;
	UPROPERTY(meta = (BindWidget))
	UCircularThrobber* LoadIcon;
protected:
	UPROPERTY()
	ACropoutGameMode* CropoutGameMode;
private:
	UPROPERTY()
	UWidgetAnimation* BackGroundImageFadeInAnimation;
	UPROPERTY()
	UWidgetAnimation* LoadIconFadeInAnimation;
	UPROPERTY()
	UWidgetAnimation* LoadAnimation;
	FTimerHandle DelayTimer;
public:
	UFUNCTION(BlueprintCallable)
	void InitializeAnimation(UWidgetAnimation* BackGroundImageFadeIn,UWidgetAnimation* LoadIconFadeIn, UWidgetAnimation* Animation_Load);
	UFUNCTION()
	void PlayLoadAnimation(EUMGSequencePlayMode::Type PlayMode, float PlayRate);
	
	UFUNCTION()
	void OnGameCompleteInitialization();

private:
	UFUNCTION()
	void DisplayBackGroundImage();
	UFUNCTION()
	void HideBackGroundImage();
	UFUNCTION()
	void DisplayLoadIcon();
	UFUNCTION()
	void HideLoadIcon();

};
