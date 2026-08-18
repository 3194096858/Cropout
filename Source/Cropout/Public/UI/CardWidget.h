
#pragma once
#include "Enum/ResourceType.h"
#include "Enum/GameObjectType/GameObjectType.h"
#include "Struct/CardInformation.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CardWidget.generated.h"

DECLARE_DELEGATE(FOnClick);
DECLARE_DELEGATE(FOnHover);
DECLARE_DELEGATE(FOnUnhover);

class ACropoutGameMode;
class UButton;
class UTextBlock;
class UImage;
class UTexture2D;


UCLASS()
class CROPOUT_API UCardWidget : public UUserWidget
{
	GENERATED_BODY()
	

private:
	virtual void NativePreConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeOnInitialized() override;

public:
	UPROPERTY(meta = (BindWidget))
	UButton* Button;
	UPROPERTY(meta = (BindWidget))
	UImage* CardIcon;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CardName;
	UPROPERTY(meta = (BindWidget),BlueprintReadWrite)
	UTextBlock* FoodCost;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UTextBlock* WoodCost;
	UPROPERTY(meta = (BindWidget), BlueprintReadWrite)
	UTextBlock* StoneCost;
	FOnClick OnClick;
	FOnClick OnHover;
	FOnClick OnUnhover;

	
private:
	FCardInformation CardInformation;
	UPROPERTY()
	UWidgetAnimation* HoverVFXAnimation;
private:

public:
	UFUNCTION(BlueprintCallable)
	void InitializeAnimation(UWidgetAnimation* Animation_HoverVFX);
	UFUNCTION()
	FCardInformation& GetCardInformation();
	UFUNCTION()
	void OnClickButton();
	UFUNCTION()
	void OnHoverButton();
	UFUNCTION()
	void OnUnhoverButton();
	UFUNCTION()
	void SetCardIcon(UTexture2D* Icon);
	UFUNCTION()
	void SetCardCost(TMap<EResourceType,int32> CostMap);
	UFUNCTION()
    void SetCardName(FName Name);



};
