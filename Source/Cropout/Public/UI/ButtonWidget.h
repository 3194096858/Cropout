
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ButtonWidget.generated.h"


DECLARE_DELEGATE(FOnClick);


class ACropoutGameMode;
class UButton;
class UTextBlock;
class UImage;
class UTexture2D;



UCLASS()
class CROPOUT_API UButtonWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	virtual void NativePreConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeOnInitialized() override;

//***********************变量
public:
	UPROPERTY(meta = (BindWidget))
	UButton* Button;
	UPROPERTY(meta = (BindWidget))
	UImage* Image;
    UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBlock;
	UPROPERTY(EditAnywhere)
	UTexture2D* IconTexture;
	UPROPERTY(EditAnywhere)
	FText Text = FText::FromString("Text!!!");
	UPROPERTY(EditAnywhere)
	float FontSize = 32.0f;
    UPROPERTY(EditAnywhere)
	bool IsShowIcon = true;
    UPROPERTY(EditAnywhere)
	bool IsShowText = false;
	UPROPERTY(EditAnywhere)
	FSlateBrush NormalStyle;
    UPROPERTY(EditAnywhere)
	FSlateBrush HoverStyle;
	UPROPERTY(EditAnywhere)
	FSlateBrush PressStyle;
	FOnClick OnClick;

private:

	//***********************函数
public:
    UFUNCTION()
    void OnClickButton();
	/*UFUNCTION()
	void OnHoverButton();*/


};
