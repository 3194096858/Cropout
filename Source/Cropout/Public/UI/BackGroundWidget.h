
#pragma once

#include "Enum/WidgetType.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BackGroundWidget.generated.h"

class ACropoutGameMode;
class UWidgetAnimation;
class UTexture2D;
class UImage;
UCLASS()
class CROPOUT_API UBackGroundWidget : public UUserWidget
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
	UPROPERTY(EditAnywhere,Category = "Widget")
	TMap<EWidgetType,FSlateBrush> ImageBrushMap;
	UPROPERTY(EditAnywhere,Category = "Widget")
	EWidgetType PreviewWidgetType = EWidgetType::Start;

protected:
	UPROPERTY()
	ACropoutGameMode* CropoutGameMode;
private:
	
public:
	/*UFUNCTION(BlueprintCallable)
	void InitializeAnimation(UWidgetAnimation* Load);*/
    UFUNCTION()
    void SetBackGroundImage(EWidgetType Widget);
	UFUNCTION()
	void OnGameCompleteInitialization();
	UFUNCTION()
	void OnGameStart();

};
