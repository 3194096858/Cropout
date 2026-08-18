// Fill out your copyright notice in the Description page of Project Settings.


#include "GameObject/Stone.h"

#include "Components/DecalComponent.h"

#include "Component/HealthComponent.h"

#include "Component/CollisionDetectionComponent.h"

#include "Enum/ObjectPoolType.h"

#include "GameMode/CropoutGameMode.h"
#include "GameInstance/CropoutGameInstance.h"
#include "Manager/DelegateManager.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/DecalManager.h"

#include "Components/CapsuleComponent.h"


AStone::AStone()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	SetGameObjectType(EGameObjectType::Stone);
	GetHealthComponent()->SetCurrentHealth(100.0f);
	this->CapsuleComponent->SetCapsuleSize(150.0f, 150.0f);
	SetRelatedObjectPoolType(EObjectPoolType::Stone);


}

void AStone::BeginPlay()
{
	Super::BeginPlay();



}

void AStone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}




void AStone::OnObjectBeginPlay(AActor* Object)
{
	Super::OnObjectBeginPlay(Object);

	if (Object != this)
	{
		return;
	}
	
	auto Lambda = [this]()
		{
			this->CollisionDetectionComponent->LineTraceForObject(GetActorLocation(), GetActorLocation() + GetActorUpVector() * -999.0f, this->CollisionDetectionComponent->DefaultObjectTypeQueryArray);
			FHitResult HitResult = this->CollisionDetectionComponent->GetFirstHitResult();
			this->DecalComponent = this->CropoutGameMode->GetGameInstance()->GetDecalManager()->SpawnDecalAtLocation(this, this->Decal, GetActorLocation(), HitResult.Normal.Rotation() + FRotator(0.0f, FMath::RandRange(0.0f, 180.0f), 0.0f), FVector(150.0f) * GetActorScale3D());

		};
	GetWorld()->GetTimerManager().ClearTimer(this->DelayTimer);
	GetWorld()->GetTimerManager().SetTimer(this->DelayTimer, Lambda, 0.3f, false);
	

}


void AStone::OnObjectEndPlay(AActor* Object)
{
	Super::OnObjectEndPlay(Object);
	if (Object != this)
	{
		return;
	}
	this->CropoutGameMode->GetGameInstance()->GetDecalManager()->DestroyDecal(this->DecalComponent, 3.0f, 1.0f);


}

void AStone::OnReduceHealth(float Damage, AActor* CauserActor)
{
	Super::OnReduceHealth(Damage, CauserActor);
	TMap<EResourceType, int> ResourceMap;
	ResourceMap.Add(EResourceType::Food, 0);
	ResourceMap.Add(EResourceType::Wood, 0);
	ResourceMap.Add(EResourceType::Stone, 10);
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnVillagerResourceIncrease.Broadcast(CauserActor, ResourceMap);



}


void AStone::OnDied()
{
	Super::OnDied();

	auto Lambda = [this]()
		{
			this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectEnterPool.Broadcast(this, EObjectPoolType::Stone);
		};
	GetWorld()->GetTimerManager().SetTimer(this->DelayTimer, Lambda, 1.0f, false);
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnVillagerCompleteJob.Broadcast(GetActorLocation());



}


void AStone::OnPlayerReturnStartMenu()
{
	Super::OnPlayerReturnStartMenu();
	
}



