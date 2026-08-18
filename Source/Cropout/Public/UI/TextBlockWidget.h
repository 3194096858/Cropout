
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TextBlockWidget.generated.h"

class UTextBlock;
class ACropoutGameMode;
class UWidgetAnimation;
class UTexture2D;
class UImage;
class USizeBox;
UCLASS()
class CROPOUT_API UTextBlockWidget : public UUserWidget
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
	UImage* BackGroundImage;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock;
	UPROPERTY(EditAnywhere)
	FSlateBrush ImageBrush;
	UPROPERTY(EditAnywhere)
	FSlateFontInfo FontInformation;
	UPROPERTY(EditAnywhere)
    bool IsShowBackGroundImage = true;
	UPROPERTY(EditAnywhere)
	FText Text = FText::FromString("Text!!!");
protected:
	UPROPERTY()
	UWidgetAnimation* DamageTextAnimation;
private:

public:
	UFUNCTION(BlueprintCallable)
	void InitializeAnimation(UWidgetAnimation* Animation_DamageText);
	void SetText(FText NewText);
	void SetText(int32 NewText);
	UFUNCTION()
	void SetFontInformation(float NewSize);
	UFUNCTION()
	void PlayDamageTextAnimation(float PlayRate = 1.0f);
	UFUNCTION()
	void SetSize(float Width, float Height);
	UFUNCTION()
	float GetWidth();
	UFUNCTION()
	float GetHeight();
	UFUNCTION()
	float GetTextBlockRenderOpacity();
private:
	UPROPERTY()
	ACropoutGameMode* CropoutGameMode;

};
