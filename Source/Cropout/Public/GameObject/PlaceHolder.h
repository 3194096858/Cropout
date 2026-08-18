
#pragma once

#include "Struct/CardInformation.h"


#include "CoreMinimal.h"
#include "GameObject/GameObject.h"
#include "PlaceHolder.generated.h"


class UTimelineComponent;
class UCurveFloat;



UCLASS()
class CROPOUT_API APlaceHolder : public AGameObject
{
	GENERATED_BODY()
public:
	APlaceHolder();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
	//*********************************变量
public:
	UPROPERTY(EditAnywhere, Category = "Component")
    UStaticMeshComponent* PlacementVFXMesh;
	UPROPERTY(EditAnywhere, Category = "Component")
	UStaticMeshComponent* CircleRingVFXMesh;
	UPROPERTY(EditAnywhere, Category = "Component")
	TMap<EGameObjectType, UStaticMesh*> GameObjectMeshMap;
	UPROPERTY(EditAnywhere, Category = "Component")
	UTimelineComponent* TimelineComponent;
	UPROPERTY(EditAnywhere, Category = "Curve")
	UCurveFloat* Curve_010;
private:
	FName SelectedObjectName;
	FTimerHandle InitializationTimer;
	bool CanPlace = false;
	TMap<EGameObjectType, float > FloatingMinScaleMap;
	float FloatingAmplitude = 1.1f;
	FVector FloatingStartScale;
	FVector FloatingEndScale;
protected:
	virtual void OnObjectBeginPlay(AActor* Object) override;
	virtual void OnObjectEndPlay(AActor* Object) override;

private:
	UFUNCTION()
	void InitializeAnimation();
	UFUNCTION()
	void PlayAnimation(UTimelineComponent* Timeline, bool IsPlayFromStart = true, bool IsLooping = false, float PlayRate = 1.0f);
	UFUNCTION()
	void SetFloatingAnimation(float Value);
	UFUNCTION()
	void InitializeMinFloatingSizeMap();
	UFUNCTION()
	void OnPlayerPlaceGameObject(const FCardInformation& SelectedCard);
	UFUNCTION()
	void OnMouseMove(const FVector& MouseLocation);
	UFUNCTION()
	void OnGameOver();
	UFUNCTION()
	void OnGameWin();
	UFUNCTION()
	void OnPlayerSelectCard(const FCardInformation& SelectedCard);
	UFUNCTION()
	void UpdateGameObjectMesh(const FName& ObjectName);
	UFUNCTION()
	void OnPlayerRotateGameObject();
	UFUNCTION()
	void OnPlayerCloseCardOperationPanel();


};
