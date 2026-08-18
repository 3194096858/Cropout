// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPool/CornFieldObjectPool.h"




ACornFieldObjectPool::ACornFieldObjectPool()
{
	PrimaryActorTick.bCanEverTick = false;
	SetObjectPoolType(EObjectPoolType::CornField);
	this->PoolSize = 50;

}

void ACornFieldObjectPool::BeginPlay()
{
	Super::BeginPlay();




}

void ACornFieldObjectPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}