
#pragma once

#include "Enum/GameObjectType/GameObjectType.h"

#include "Enum/ObjectPoolType.h"
#include "Enum/ResourceType.h"
#include "Struct/CardInformation.h"
#include "Enum/WidgetType.h"
#include "Enum/GameStatus.h"


#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CropoutGameMode.generated.h"

class UCropoutGameInstance;
class ACropoutObjectPool;
class AGuidanceLineSegmentObjectPool;
class ACircleRingObjectPool;
class ATreeObjectPool;
class AStoneObjectPool;
class AShrubObjectPool;
class ATownHallObjectPool;
class AGameObjectGenerator;
class AGrassObjectPool;
class UDataTable;
class APlaceHolderObjectPool;
class AMonumentObjectPool;
class AVillagerHouseObjectPool;
class AVillagerObjectPool;
class ACornFieldObjectPool;
class AWheatFieldObjectPool;
class APumpkinFieldObjectPool;
class ALettuceFieldObjectPool;


UCLASS()
class CROPOUT_API ACropoutGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	ACropoutGameMode();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:
	UPROPERTY(EditAnywhere, Category = "UI")
    TMap<EWidgetType, UClass*> WidgetClassMap;
	UPROPERTY(EditAnywhere, Category = "ObjectPool")
	TMap<EObjectPoolType,UClass*> ObjectPoolClassMap;
	UPROPERTY(EditAnywhere, Category = "Generator")
	UClass* GameObjectGeneratorClass;
	UPROPERTY(EditAnywhere, Category = "DataTable")
	UDataTable* CardInformationTable;
private:
    UPROPERTY()
	UCropoutGameInstance* CropoutGameInstance;
	UPROPERTY()
	AGuidanceLineSegmentObjectPool* GuidanceLineSegmentObjectPool;
	UPROPERTY()
	ACircleRingObjectPool* CircleRingObjectPool;
    UPROPERTY()
    ATreeObjectPool* TreeObjectPool;
    UPROPERTY()
    AStoneObjectPool* StoneObjectPool;
    UPROPERTY()
    AShrubObjectPool* ShrubObjectPool;
	UPROPERTY()
	AGrassObjectPool* GrassObjectPool;
    UPROPERTY()
    ATownHallObjectPool* TownHallObjectPool;
	UPROPERTY()
	APlaceHolderObjectPool* PlaceHolderObjectPool;
	UPROPERTY()
	AVillagerHouseObjectPool* VillagerHouseObjectPool;
	UPROPERTY()
	AMonumentObjectPool* MonumentObjectPool;
	UPROPERTY()
	ACornFieldObjectPool* CornFieldObjectPool;
	UPROPERTY()
	AWheatFieldObjectPool* WheatFieldObjectPool;
	UPROPERTY()
	APumpkinFieldObjectPool* PumpkinFieldObjectPool;
	UPROPERTY()
	ALettuceFieldObjectPool* LettuceFieldObjectPool;
	UPROPERTY()
	AVillagerObjectPool* VillagerObjectPool;
	FTimerHandle TickTimer;
	FTimerHandle InitializationTimer;
	FVector MouseLocation;
public:
	UFUNCTION()
	bool CheckObjectPoolIsEmpty(EObjectPoolType PoolType);
	UFUNCTION()
	void TickFunction();
	UFUNCTION()
	TArray<FName> GetAllActiveObjectName(EObjectPoolType PoolType);
	UFUNCTION()
	UClass* GetGameObjectGeneratorClass();
    UFUNCTION()
	UClass* GetTextBlockWidgetClass();
	UFUNCTION()
	UClass* GetProgressBarWidgetClass();
	FORCEINLINE UCropoutGameInstance* GetGameInstance() const
	{
		return this->CropoutGameInstance;
	};
	UFUNCTION()
	void OnPlayerReturnStartMenu();
	UFUNCTION()
	TArray<AActor*> GetGuidanceLineSegmentArray();
	UFUNCTION()
	void SpawnObjectPool();
	UFUNCTION()
	void SetMouseLocation(FVector NewLocation);
    UFUNCTION()
	FVector GetMouseLocation();
	UFUNCTION()
	FVector GetTownHallLocation();
	UFUNCTION()
	bool CheckActorIsActive(AActor* Object, EObjectPoolType PoolType);
	UFUNCTION()
	FCardInformation GetCardInformationFromTable(FName CardName);
private:
	UFUNCTION()
	void SpawnTreeByGenerator();
	UFUNCTION()
	void SpawnTownHallByGenerator();
	UFUNCTION()
	void SpawnStoneByGenerator();
	UFUNCTION()
	void SpawnShrubByGenerator();
	UFUNCTION()
	void SpawnGrassByGenerator();
	UFUNCTION()
	void OnGameOver();
	UFUNCTION()
	void OnGameWin();
	UFUNCTION()
	void OnGameSave();
	UFUNCTION()
	void OnGameQuit();
	UFUNCTION()
	void OnGameStart();
	UFUNCTION()
	void OnGameRestart();
	UFUNCTION()
	void OnGamePause();
	UFUNCTION()
	void OnGameResume(EGameStatus CurrentStatus);
	UFUNCTION()
	void OnGameStartInitialization();
	UFUNCTION()
	void OnGameCompleteInitialization();
	UFUNCTION()
	void OnPlayerOpenCardSelectionPanel();
	UFUNCTION()
	void OnPlayerCloseCardSelectionPanel();
};
