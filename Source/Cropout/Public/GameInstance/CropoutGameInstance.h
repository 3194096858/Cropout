
#pragma once
#include "Enum/WidgetType.h"
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CropoutGameInstance.generated.h"

class UDelegateManager;
class UDecalManager;
class UWidgetManager;
class UDataManager;
class ULevelManager;
UCLASS()
class CROPOUT_API UCropoutGameInstance : public UGameInstance
{
	GENERATED_BODY()
private:
	UCropoutGameInstance();
	virtual void Init() override;
	virtual void OnStart() override;

public:
	
private:
	UPROPERTY()
	UDelegateManager* DelegateManager;
	UPROPERTY()
	UDecalManager* DecalManager;
	UPROPERTY()
	UWidgetManager* WidgetManager;
	UPROPERTY(VisibleAnywhere, Category = "Manager")
    UDataManager* DataManager;
	UPROPERTY()
	ULevelManager* LevelManager;
public:
	FORCEINLINE UDelegateManager* GetDelegateManager() const
	{
		return DelegateManager;
	};
	FORCEINLINE UDecalManager* GetDecalManager() const
	{
		return DecalManager;
	};
	FORCEINLINE UWidgetManager* GetWidgetManager() const
	{
		return WidgetManager;
	};
    FORCEINLINE UDataManager* GetDataManager() const
	{
		return DataManager;
	};
	FORCEINLINE ULevelManager* GetLevelManager() const
	{
		return LevelManager;
	};
private:
	UFUNCTION()
	void InitializeManager();
	

};
