
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserTipWidget.generated.h"

class UCanvasPanel;
class UTextBlockWidget;
class UTextBlock;
class ACropoutGameMode;
class UWidgetAnimation;
class UTexture2D;
class UImage;

UCLASS()
class CROPOUT_API UUserTipWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	virtual void NativePreConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeOnInitialized() override;
	virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;
public:
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* CanvasPanel;
	UPROPERTY(meta = (BindWidget))
	UTextBlockWidget* PlacementTip;
	UPROPERTY(meta = (BindWidget))
	UTextBlockWidget* SaveGameTip;
	UPROPERTY(meta = (BindWidget))
	UTextBlockWidget* ResourceTip;
	UPROPERTY(meta = (BindWidget))
	UTextBlockWidget* ObjectCountTip;
protected:
	UPROPERTY()
	ACropoutGameMode* CropoutGameMode;
private:
	UPROPERTY()
	UWidgetAnimation* PlacementTipAnimation;
	UPROPERTY()
	UWidgetAnimation* SaveGameTipAnimation;
	UPROPERTY()
	UWidgetAnimation* ResourceTipAnimation;
	UPROPERTY()
	UWidgetAnimation* ObjectCountTipAnimation;
	UPROPERTY()
	TMap<FName, UTextBlockWidget*> DamageTextMap;
public:
	UFUNCTION(BlueprintCallable)
	void InitializeAnimation(UWidgetAnimation* Animation_PlacementTip, UWidgetAnimation* Animation_SaveGameTip, UWidgetAnimation* Animation_ResourceTip, UWidgetAnimation* Animation_ObjectCountTip);
	UFUNCTION()
	void DisplayPlacementTip();
	UFUNCTION()
	void DisplaySaveGameTip();
	UFUNCTION()
	void DisplayResourceTip();
	UFUNCTION()
	void DisplayObjectCountTip();
	UFUNCTION()
	void AddWidgetToCanvasPanel(UUserWidget* Widget);
	UFUNCTION()
	void RemoveWidgetFromCanvasPanel(UUserWidget* Widget);


private:
	
};
