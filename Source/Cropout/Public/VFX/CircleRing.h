// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Enum/GameObjectType/GameObjectType.h"
#include "Interface/GameObjectTypeInterface.h"

#include "CoreMinimal.h"
#include "VFX/VFX.h"
#include "CircleRing.generated.h"

class UTimelineComponent;
class UCurveFloat;



UCLASS()
class CROPOUT_API ACircleRing : public AVFX, public IGameObjectTypeInterface
{
	GENERATED_BODY()

public:
	ACircleRing();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
//****************************变量
public:
	UPROPERTY(EditAnywhere, Category = "Curve")
	UCurveFloat* Curve_010;
	UPROPERTY(EditAnywhere, Category = "Curve")
	UCurveFloat* Curve_01;
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UTimelineComponent* TimelineComponent_Floating;
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UTimelineComponent* TimelineComponent_Absorption;
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UTimelineComponent* TimelineComponent_Separation;
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UTimelineComponent* TimelineComponent_BeginPlay;
	FVector OriginalMeshScale;
	FVector AbsorptionStartLocation;
	FVector AbsorptionEndLocation;
	FVector AbsorptionStarScale;
	FVector AbsorptionEndScale;
	FVector SeparationStartLocation;
	FVector SeparationStartScale;
	FVector FloatingStartScale;
	FVector FloatingEndScale;
	TMap<EGameObjectType,float > FloatingMinScaleMap;
    FTimerHandle SeparationTimer;
	bool IsAbsorb = false;
	bool CanMove = true;
	float FloatingAmplitude = 1.1f;
	UPROPERTY()
	AActor* LastAborptionTarget = nullptr;
	UPROPERTY()
	AActor* CurrentAborptionTarget = nullptr;
	EGameObjectType GameObjectType = EGameObjectType::None;


//***************************函数
public:


protected:
	virtual void OnObjectBeginPlay(AActor* Object) override;
	virtual void OnObjectEndPlay(AActor* Object) override;
	virtual void SetGameObjectType(EGameObjectType NewType) override;
	virtual EGameObjectType GetGameObjectType() override;
	virtual void OnMouseMove(const FVector& MouseLocation) override;
	virtual void OnMouseLeftKeyRelease() override;


private:
	UFUNCTION()
	void InitializeAnimation();
	UFUNCTION()
	void SearchAborptionTarget();
	UFUNCTION()
	void PlayAnimation(UTimelineComponent* Timeline ,bool IsPlayFromStart = true, bool IsLooping = false, float PlayRate = 1.0f);
	UFUNCTION()
	void SetFloatingAnimation(float Value);
	UFUNCTION()
	void SetAbsorptionAnimation(float Value);
	UFUNCTION()
	void SetSeparationAnimation(float Value);
	UFUNCTION()
	void SetBeginPlayAnimation(float Value);
	UFUNCTION()
	void InitializeMinFloatingSizeMap();
	UFUNCTION()
	void AbsorbToTarget();
	UFUNCTION()
	void DetachFromTarget();
	UFUNCTION()
	void OnBeginPlayAnimationFinished();
	UFUNCTION()
	void OnAbsorptionAnimationFinished();
	UFUNCTION()
	void OnSeparationAnimationFinished();

};
