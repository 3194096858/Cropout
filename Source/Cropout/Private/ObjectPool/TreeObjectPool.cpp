

#include "ObjectPool/TreeObjectPool.h"



ATreeObjectPool::ATreeObjectPool()
{
	PrimaryActorTick.bCanEverTick = true;
	
	SetObjectPoolType(EObjectPoolType::Tree);
	this->PoolSize = 70;

}

void ATreeObjectPool::BeginPlay()
{
	Super::BeginPlay();
	



}

void ATreeObjectPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}