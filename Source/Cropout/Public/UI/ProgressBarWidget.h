
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProgressBarWidget.generated.h"

class UTextBlock;
class ACropoutGameMode;
class UWidgetAnimation;
class UTexture2D;
class UImage;
class UProgressBar;
class USizeBox;

UCLASS()
class CROPOUT_API UProgressBarWidget : public UUserWidget
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
	UProgressBar* ProgressBar;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock;
	UPROPERTY(EditAnywhere)
	FSlateFontInfo FontInformation;
	UPROPERTY(EditAnywhere)
	bool IsShowText = true;
	UPROPERTY(EditAnywhere)
	FText Text = FText::FromString("Text!!!");
protected:
	UPROPERTY()
	ACropoutGameMode* CropoutGameMode;
private:
	FProgressBarStyle Style;
	UPROPERTY()
	UWidgetAnimation* FadeInAnimation;
public:
	UFUNCTION(BlueprintCallable)
	void InitializeAnimation(UWidgetAnimation* Animation_FadeIn);
	UFUNCTION()
	void SetBackGroundImageStyle(ESlateBrushDrawType::Type DrawType, ESlateBrushRoundingType::Type RoundingType,const FVector4& CornerRadious,float Width,const FColor& ImageColor);
	UFUNCTION()
	void SetFillImageStyle(ESlateBrushDrawType::Type DrawType, ESlateBrushRoundingType::Type RoundingType, const FVector4& CornerRadious, float Width, const FColor& ImageColor);
	UFUNCTION()
	void SetPercent(float NewPercent);
	UFUNCTION()
	void SetSize(float Width,float Height);
	UFUNCTION()
	float GetWidth();
	UFUNCTION()
	float GetHeight();
	UFUNCTION()
	void PlayFadeInAnimation(float PlayRate);
	UFUNCTION()
	void PlayFadeOutAnimation(float PlayRate);
	UFUNCTION()
	float GetSizeBoxRenderOpacity();


};
