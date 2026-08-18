// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SliderWidget.generated.h"

DECLARE_DELEGATE_OneParam(FOnValueChange, float);

class UTextBlock;
class ACropoutGameMode;
class UWidgetAnimation;
class UTexture2D;
class UImage;
class USizeBox;
class USlider;


UCLASS()
class CROPOUT_API USliderWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	virtual void NativePreConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeOnInitialized() override;
public:
	UPROPERTY(meta = (BindWidget))
	USizeBox* SizeBox;
	UPROPERTY(meta = (BindWidget))
	USlider* Slider;
	UPROPERTY(meta = (BindWidget))
	UImage* BackGroundImage;
	UPROPERTY(EditAnywhere)
	FSlateBrush ImageBrush;
	UPROPERTY(EditAnywhere)
	bool IsShowBackGroundImage = true;
	FOnValueChange OnValueChange;

protected:



private:
	UPROPERTY()
	ACropoutGameMode* CropoutGameMode;
public:
	/*UFUNCTION(BlueprintCallable)
	void InitializeAnimation(UWidgetAnimation* Animation_DamageText);
	*/
	UFUNCTION()
	void OnSliderValueChange(float Value);
	UFUNCTION()
	void SetSize(float Width, float Height);
	UFUNCTION()
	float GetWidth();
	UFUNCTION()
	float GetHeight();
	UFUNCTION()
	void SetValue(float NewValue);

};
