
#pragma once
#include "Enum/ResourceType.h"
#include "Enum/GameStatus.h"
#include "Enum/NPCState/NPCState.h"
#include "Enum/ObjectPoolType.h"
#include "Struct/CardInformation.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DelegateManager.generated.h"


//***避免预处理器将 模板类型中的逗号 误认为是分隔不同宏参数的逗号***//
using ResourceMapType = TMap<EResourceType, int32>;


//**********************
DECLARE_MULTICAST_DELEGATE(FOnPlayerOpenCardSelectionPanel);
DECLARE_MULTICAST_DELEGATE(FOnPlayerCloseCardSelectionPanel);
DECLARE_MULTICAST_DELEGATE(FOnPlayerCloseCardOperationPanel);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerSelectCard,const FCardInformation&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerPlaceGameObject, const FCardInformation&);
DECLARE_MULTICAST_DELEGATE(FOnPlayerRotateGameObject);
DECLARE_MULTICAST_DELEGATE(FOnPlayerReturnStartMenu);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerResourceIncrease, ResourceMapType);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPlayerResourceReduce, ResourceMapType);

//****************
DECLARE_MULTICAST_DELEGATE(FOnGameWin);
DECLARE_MULTICAST_DELEGATE(FOnGameStart);
DECLARE_MULTICAST_DELEGATE(FOnGameOver);
DECLARE_MULTICAST_DELEGATE(FOnGamePause);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameResume,EGameStatus);
DECLARE_MULTICAST_DELEGATE(FOnGameRestart);
DECLARE_MULTICAST_DELEGATE(FOnGameQuit);
DECLARE_MULTICAST_DELEGATE(FOnGameSave);
DECLARE_MULTICAST_DELEGATE(FOnGameCompleteInitialization);
DECLARE_MULTICAST_DELEGATE(FOnGameStartInitialization);

//*************************
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnNPCStateChange,AActor*, ENPCState);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnVillagerCompleteJob, const FVector& );
DECLARE_MULTICAST_DELEGATE_OneParam(FOnCropMature, const FVector&);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnVillagerResourceIncrease, AActor*, ResourceMapType);
DECLARE_MULTICAST_DELEGATE(FOnVillagerCompleteTransport);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnVillagerCountIncrease, int32);

//************
DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnObjectLeavePool, AActor*, const FTransform&, EObjectPoolType);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnObjectEnterPool, AActor*, EObjectPoolType);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnObjectBeginPlay, AActor*);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnObjectEndPlay, AActor*);

//*************************
DECLARE_MULTICAST_DELEGATE_OneParam(FOnMouseMove, const FVector&);
DECLARE_MULTICAST_DELEGATE(FOnMouseLeftKeyRelease);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnMouseLeftKeyPress, const FVector&);

//*************************
DECLARE_MULTICAST_DELEGATE(FOnInitializeGuidanceLine);




UCLASS()
class CROPOUT_API UDelegateManager : public UObject
{
	GENERATED_BODY()
public:
    FOnGameWin OnGameWin;
    FOnGameSave OnGameSave;
	FOnGameStart OnGameStart;
    FOnGameOver OnGameOver;
    FOnGamePause OnGamePause;
    FOnGameResume OnGameResume;
    FOnGameQuit OnGameQuit;
    FOnGameRestart OnGameRestart;
    FOnNPCStateChange OnNPCStateChange;
    FOnObjectLeavePool OnObjectLeavePool;
    FOnObjectEnterPool OnObjectEnterPool;
    FOnMouseMove OnMouseMove;
    FOnMouseLeftKeyRelease OnMouseLeftKeyRelease;
    FOnMouseLeftKeyPress OnMouseLeftKeyPress;
    FOnGameCompleteInitialization OnGameCompleteInitialization;
    FOnGameStartInitialization OnGameStartInitialization;
    FOnVillagerCompleteJob OnVillagerCompleteJob;
    FOnInitializeGuidanceLine OnInitializeGuidanceLine;
    FOnObjectBeginPlay OnObjectBeginPlay;
    FOnObjectEndPlay OnObjectEndPlay;
    FOnPlayerOpenCardSelectionPanel OnPlayerOpenCardSelectionPanel;
    FOnPlayerCloseCardSelectionPanel OnPlayerCloseCardSelectionPanel;
    FOnPlayerPlaceGameObject OnPlayerPlaceGameObject;
    FOnPlayerSelectCard OnPlayerSelectCard;
    FOnPlayerRotateGameObject OnPlayerRotateGameObject;
    FOnPlayerCloseCardOperationPanel OnPlayerCloseCardOperationPanel;
    FOnCropMature OnCropMature;
    FOnPlayerReturnStartMenu OnPlayerReturnStartMenu;
    FOnVillagerResourceIncrease OnVillagerResourceIncrease;
    FOnPlayerResourceIncrease OnPlayerResourceIncrease;
    FOnPlayerResourceReduce OnPlayerResourceReduce;
    FOnVillagerCompleteTransport OnVillagerCompleteTransport;
    FOnVillagerCountIncrease OnVillagerCountIncrease;



























};
