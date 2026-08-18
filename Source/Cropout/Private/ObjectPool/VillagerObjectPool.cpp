// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPool/VillagerObjectPool.h"



AVillagerObjectPool::AVillagerObjectPool()
{
	PrimaryActorTick.bCanEverTick = false;

	SetObjectPoolType(EObjectPoolType::Villager);
	this->PoolSize = 50;

}

void AVillagerObjectPool::BeginPlay()
{
	Super::BeginPlay();




}

void AVillagerObjectPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}