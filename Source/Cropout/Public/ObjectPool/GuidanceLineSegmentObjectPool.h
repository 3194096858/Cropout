// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectPool/CropoutObjectPool.h"
#include "GuidanceLineSegmentObjectPool.generated.h"

/**
 * 
 */
UCLASS()
class CROPOUT_API AGuidanceLineSegmentObjectPool : public ACropoutObjectPool
{
	GENERATED_BODY()

public:
	AGuidanceLineSegmentObjectPool();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
public:

private:
	FTimerHandle GuidanceLineTimer;
	FTimerHandle InitializationTimer;
	TArray<AActor*> GuidanceLineSegmentArray;
	//FVector MouseWorldLocation;
	//AActor* SelectedNPC;
public:
	TArray<AActor*> GetGuidanceLineSegmentArray();
protected:
	virtual void ObjectBeginPlay(AActor* Object, const FTransform& ObjectTransform)override;
	virtual void ObjectEndPlay(AActor* Object) override;
	virtual void OnObjectLeavePool(AActor* Object, const FTransform& ObjectTransform, EObjectPoolType TargetObjectPoolType) override;
	virtual void OnObjectEnterPool(AActor* Object, EObjectPoolType TargetObjectPoolType) override;

private:
	virtual void OnMouseMove(const FVector& MouseLocation) override;
	virtual void OnMouseLeftKeyRelease() override;
	virtual void OnMouseLeftKeyPress(const FVector& MouseLocation) override;
	
	UFUNCTION()
	void OnInitializeGuidanceLine();

};
