// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPool/WheatFieldObjectPool.h"




AWheatFieldObjectPool::AWheatFieldObjectPool()
{
	PrimaryActorTick.bCanEverTick = false;
	SetObjectPoolType(EObjectPoolType::WheatField);
	this->PoolSize = 50;

}

void AWheatFieldObjectPool::BeginPlay()
{
	Super::BeginPlay();




}

void AWheatFieldObjectPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}