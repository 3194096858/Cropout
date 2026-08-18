
#pragma once

#include "Enum/PlayerOperationMode.h"
#include "Struct/PlayerCollisionDetectionInformation.h"
#include "Struct/CardInformation.h"
#include "Enum/GameStatus.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CropoutPlayer.generated.h"



class USplineComponent;
class ACropoutGameMode;
class UCameraComponent;
class USpringArmComponent;
class USceneComponent;
class UCollisionDetectionComponent;

UCLASS()
class CROPOUT_API ACropoutPlayer : public APawn
{
	GENERATED_BODY()
public:
	ACropoutPlayer();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
//**************************变量
public:
	/*UPROPERTY(EditAnywhere, Category = "Default")
	TMap<FString, TArray<TEnumAsByte<EObjectTypeQuery>>> ObjectTypeQueryMap;*/

	/*UPROPERTY(EditAnywhere, Category = "Default")
	TMap<EPlayerOperationMode,int32> a1111;*/

	/*UPROPERTY(EditAnywhere, Category = "Default")
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypeQuery;*/
	UPROPERTY(EditAnywhere, Category = "Default")
	struct FPlayerCollisionDetectionInformation DetectionInformation_MouseLeftKeyPress;
	UPROPERTY(EditAnywhere, Category = "Default")
	struct FPlayerCollisionDetectionInformation DetectionInformation_MouseLeftKeyRelease;
	UPROPERTY(EditAnywhere, Category = "Default")
	struct FPlayerCollisionDetectionInformation DetectionInformation_MouseMovement;
	
protected:
	UPROPERTY()
	ACropoutGameMode* CropoutGameMode;
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UCameraComponent* CameraComponent;
	UPROPERTY(VisibleAnywhere, Category = "Component")
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere, Category = "Component")
	USceneComponent* SceneComponent;
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UCollisionDetectionComponent* CollisionDetectionComponent;
	UPROPERTY(VisibleAnywhere, Category = "Component")
	USplineComponent* SplineComponent;
private:
	TMap<EResourceType, int32> ResourceMap;
	TMap<EResourceType, int32> MaxResourceMap;
	UPROPERTY()
	AActor* SelectedNPC;
	UPROPERTY()
	TArray<AActor*> GuidanceLineSegmentArray;
	FVector MouseLocation;
	int32 MaxGuidanceLineSegmentNumber = 30;
	FTimerHandle GuidanceLineTimer;
	EPlayerOperationMode PlayerOperationMode = EPlayerOperationMode::None;

	
public:

private:
	//UFUNCTION()
	//void OnPlayerReturnStartMenu();
	UFUNCTION()
	void OnGameStartInitialization();
	UFUNCTION()
	void OnPlayerResourceReduce(TMap<EResourceType, int32> OtherResource);
	UFUNCTION()
	void OnPlayerResourceIncrease(TMap<EResourceType,int32> OtherResource);
	UFUNCTION()
	void LoadDataByManager();
	UFUNCTION()
	void SaveDataToManager();
	UFUNCTION()
	void OnPlayerSelectCard(const FCardInformation& SelectedCard);
	UFUNCTION()
	void OnPlayerPlaceGameObject(const FCardInformation& SelectedCard);
	UFUNCTION()
	void OnGameWin();
	UFUNCTION()
	void OnGameSave();
	UFUNCTION()
	void OnGameStart();
	UFUNCTION()
	void OnGameRestart();
	UFUNCTION()
	void OnGamePause();
	UFUNCTION()
	void OnGameResume(EGameStatus CurrentStatus);
	UFUNCTION()
	void OnMouseMove(const FInputActionValue& Value);
	UFUNCTION()
    void OnMouseLeftKeyPress(const FInputActionValue& Value);
	UFUNCTION()
	void OnMouseLeftKeyRelease(const FInputActionValue& Value);
    UFUNCTION()
    void OnMouseWheel(const FInputActionValue& Value);
	UFUNCTION()
	void UpdateScreenScale(const FInputActionValue& Value);
	UFUNCTION()
	void UpdateScreenLocation(const FInputActionValue& Value);
	UFUNCTION()
	void MouseLineTrace(TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypeQuery);
	UFUNCTION()
	void SwitchOperationMode(EGameObjectType ObjectType);
	UFUNCTION()
	void SetLastSplinePointLocation(const FVector& Location);
	UFUNCTION()
	void SetFirstSplinePointLocation(const FVector& Location);
	UFUNCTION()
	void UpdateGuidanceLineState();
	UFUNCTION()
	void RemoveGuidanceLine();
	UFUNCTION()
	void InitializeGuidanceLine(int32 LineSegmentTotal);
	UFUNCTION()
	int32 GetGuidanceLineSegmentTotal(float SplineLength);
};
