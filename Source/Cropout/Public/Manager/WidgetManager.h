
#pragma once

#include "Enum/WidgetType.h"
#include "Blueprint/UserWidget.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "WidgetManager.generated.h"

class UProgressBarWidget;
class UTextBlockWidget;
class UConstructionWidget;
class UBackGroundWidget;
class UBattleWidget;
class UStartWidget;
class UUserTipWidget;
class ULoadWidget;
class UPauseWidget;

class UVictoryWidget;
class UFailureWidget;


UCLASS()
class CROPOUT_API UWidgetManager : public UObject
{
	GENERATED_BODY()
	
public:
  

protected:

private:
    UPROPERTY()
    UVictoryWidget* VictoryWidget;
    UPROPERTY()
    UFailureWidget* FailureWidget;
    UPROPERTY()
    UBackGroundWidget* BackGroundWidget;
    UPROPERTY()
    UBattleWidget* BattleWidget;
    UPROPERTY()
    UStartWidget* StartWidget;
    UPROPERTY()
    UPauseWidget* PauseWidget;
    UPROPERTY()
    UUserTipWidget* UserTipWidget;
    UPROPERTY()
    ULoadWidget* LoadWidget;
    UPROPERTY()
    UConstructionWidget* ConstructionWidget;
    UPROPERTY()
    TArray<UUserWidget*> ActiveWidgetArray;
    UPROPERTY()
    TMap<FName, UTextBlockWidget*> DamageTextMap;
    UPROPERTY()
    TMap<FName, UProgressBarWidget*> HealthBarMap;
public:
    UFUNCTION()
    void CreateCropoutWidget(UGameInstance* GameInstance, TMap<EWidgetType, UClass*> WidgetClassMap);
    UFUNCTION()
    void AddPlacementTipToViewport();
    UFUNCTION()
    void AddResourceTipToViewport();
    UFUNCTION()
    void AddVictoryWidgetToViewport(); 
    UFUNCTION()
    void AddFailureWidgetToViewport();
    UFUNCTION()
    void AddObjectCountTipToViewport();
    UFUNCTION()
    void AddSaveGameTipToViewport();
    UFUNCTION()
    void UpdateCardOperationPanelPosition(const FVector2D& NewPosition);
    UFUNCTION()
    void OpenCardSelectionPanel();
    UFUNCTION()
    void CloseCardSelectionPanel();
    UFUNCTION()
    void OpenCardOperationPanel();
    UFUNCTION()
    void CloseCardOperationPanel();
    UFUNCTION()
    void RemoveAllWidgetFromViewport();
    UFUNCTION()
    void RemoveTopWidgetFromViewport();
    UFUNCTION()
    void AddConstructionWidgetInViewport();
    UFUNCTION()
    void AddBattleWidgetToViewport();
    UFUNCTION()
    void AddPauseWidgetToViewport();
    UFUNCTION()
    void AddLoadWidgetToViewport();
    UFUNCTION()
    void RemoveLoadWidgetFromViewport();
    UFUNCTION()
    void AddBackGroundWidgetToViewport();
    UFUNCTION()
    void RemoveBackGroundWidgetFromViewport();
    UFUNCTION()
    void AddStartWidgetToViewport();
    UFUNCTION()
    void AddUserTipWidgetYoViewport();
    UFUNCTION()
    void RemoveUserTipWidgetFromViewport();
    UFUNCTION()
    void BindDamageText(UGameInstance* GameInstance, UClass* TextBlockWidgetClass, FName ActorName);
    UFUNCTION()
    void BindHealthBar(UGameInstance* GameInstance, UClass* ProgressBarWidgetClass, FName ActorName);
    UFUNCTION()
    void UnbindDamageText(FName ActorName);
    UFUNCTION()
    void UnbindHealthBar(FName ActorName);
    UFUNCTION()
    void DisplayDamageText(FName ActorName, float Damage);
    UFUNCTION()
    void DisplayHealthBar(FName ActorName, float HealthPercent);
    UFUNCTION()
    void UpdateHealthBarPosition(FName ActorName, const FVector2D& Position);
    UFUNCTION()
    void UpdateDamageTextPosition(FName ActorName, const FVector2D& Position);
    UFUNCTION()
    void UpdateBackGroundIamge(EWidgetType Widget);
    UFUNCTION()
    void PlayLoadAnimation(EUMGSequencePlayMode::Type PlayMode, float PlayRate);
   

private:


};





































