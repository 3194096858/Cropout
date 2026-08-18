// Fill out your copyright notice in the Description page of Project Settings.


#include "GameObject/Tree.h"
#include "Component/HealthComponent.h"
#include "Components/CapsuleComponent.h"

#include "Component/CollisionDetectionComponent.h"

#include "Enum/ObjectPoolType.h"
#include "Manager/WidgetManager.h"
#include "GameMode/CropoutGameMode.h"
#include "GameInstance/CropoutGameInstance.h"
#include "Manager/DelegateManager.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Manager/DataManager.h"

ATree::ATree()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	SetGameObjectType(EGameObjectType::Tree);
	SetRelatedObjectPoolType(EObjectPoolType::Tree);
	GetHealthComponent()->SetCurrentHealth(100.0f);
	this->CapsuleComponent->SetCapsuleSize(85.0f, 440.0f);
	this->CapsuleComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 410.0f));

}

void ATree::BeginPlay()
{
	Super::BeginPlay();


}

void ATree::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ATree::LoadDataByManager()
{
	Super::LoadDataByManager();

	


}

void ATree::OnObjectBeginPlay(AActor* Object)
{
	Super::OnObjectBeginPlay(Object);
	if (Object != this)
	{
		return;
	}
	//if (this->CropoutGameMode->GetGameInstance()->GetDataManager()->CheckGameObjectDataIsExist(FName(GetName())) == false)
	//{
	//	
	//	//this->MeshComponent->SetStaticMesh(Mesh);
	//	//this->MeshComponent->SetMaterial(0, Mesh->GetMaterial(0));

	//}
	
}


void ATree::OnObjectEndPlay(AActor* Object)
{
	Super::OnObjectEndPlay(Object);
	if (Object != this)
	{
		return;
	}

}

void ATree::OnReduceHealth(float Damage, AActor* CauserActor)
{
	Super::OnReduceHealth(Damage, CauserActor);
	TMap<EResourceType, int> ResourceMap;
	ResourceMap.Add(EResourceType::Food, 0);
	ResourceMap.Add(EResourceType::Wood, 10);
	ResourceMap.Add(EResourceType::Stone, 0);
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnVillagerResourceIncrease.Broadcast(CauserActor,ResourceMap);

}


void ATree::OnDied()
{
	Super::OnDied();
	auto Lambda = [this]()
		{
			this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectEnterPool.Broadcast(this, EObjectPoolType::Tree);
		};
	GetWorld()->GetTimerManager().SetTimer(this->DelayTimer, Lambda, 1.0f, false);
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnVillagerCompleteJob.Broadcast(GetActorLocation());



}




void ATree::OnGameSave()
{
	Super::OnGameSave();
	

}


void ATree::OnPlayerReturnStartMenu()
{
	Super::OnPlayerReturnStartMenu();
	


}



