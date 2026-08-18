

#include "ObjectPool/MonumentObjectPool.h"



AMonumentObjectPool::AMonumentObjectPool()
{
	PrimaryActorTick.bCanEverTick = true;

	SetObjectPoolType(EObjectPoolType::Monument);
	this->PoolSize = 1;

}

void AMonumentObjectPool::BeginPlay()
{
	Super::BeginPlay();




}

void AMonumentObjectPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}








