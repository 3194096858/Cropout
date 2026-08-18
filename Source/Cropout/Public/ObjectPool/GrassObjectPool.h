// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectPool/CropoutObjectPool.h"
#include "GrassObjectPool.generated.h"

/**
 * 
 */
UCLASS()
class CROPOUT_API AGrassObjectPool : public ACropoutObjectPool
{
	GENERATED_BODY()

public:
	AGrassObjectPool();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
	//*************************变量
public:


};
