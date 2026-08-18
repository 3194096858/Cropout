// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPool/PumpkinFieldObjectPool.h"




APumpkinFieldObjectPool::APumpkinFieldObjectPool()
{
	PrimaryActorTick.bCanEverTick = false;
	SetObjectPoolType(EObjectPoolType::PumpkinField);
	this->PoolSize = 50;

}

void APumpkinFieldObjectPool::BeginPlay()
{
	Super::BeginPlay();




}

void APumpkinFieldObjectPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}