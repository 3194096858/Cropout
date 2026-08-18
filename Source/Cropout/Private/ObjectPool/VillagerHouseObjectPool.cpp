

#include "ObjectPool/VillagerHouseObjectPool.h"



AVillagerHouseObjectPool::AVillagerHouseObjectPool()
{
	PrimaryActorTick.bCanEverTick = true;

	SetObjectPoolType(EObjectPoolType::VillagerHouse);
	this->PoolSize = 15;

}

void AVillagerHouseObjectPool::BeginPlay()
{
	Super::BeginPlay();




}

void AVillagerHouseObjectPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}