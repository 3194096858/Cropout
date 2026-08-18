// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectPool/CropoutObjectPool.h"
#include "CircleRingObjectPool.generated.h"

/**
 * 
 */
UCLASS()
class CROPOUT_API ACircleRingObjectPool : public ACropoutObjectPool
{
	GENERATED_BODY()

public:
	ACircleRingObjectPool();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
	//*************************变量
public:

public:


private:
	virtual void OnMouseMove(const FVector& MouseLocation) override;
	virtual void OnMouseLeftKeyRelease() override;
	virtual void OnMouseLeftKeyPress(const FVector& MouseLocation) override;

};
