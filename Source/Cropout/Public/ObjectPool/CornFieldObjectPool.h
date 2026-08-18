// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectPool/CropoutObjectPool.h"
#include "CornFieldObjectPool.generated.h"

/**
 * 
 */
UCLASS()
class CROPOUT_API ACornFieldObjectPool : public ACropoutObjectPool
{
	GENERATED_BODY()
public:
	ACornFieldObjectPool();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
public:


};
