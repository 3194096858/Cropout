// Fill out your copyright notice in the Description page of Project Settings.


#include "GameObject/PumpkinField.h"


#include "Component/HealthComponent.h"
#include "Manager/DecalManager.h"
#include "GameMode/CropoutGameMode.h"
#include "GameInstance/CropoutGameInstance.h"
#include "Manager/DelegateManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Component/CollisionDetectionComponent.h"


APumpkinField::APumpkinField()
{
	SetGameObjectType(EGameObjectType::PumpkinField);
	SetMaxMaturation(4);
	SetRelatedObjectPoolType(EObjectPoolType::PumpkinField);

}

void APumpkinField::BeginPlay()
{
	Super::BeginPlay();


}

void APumpkinField::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void APumpkinField::OnObjectBeginPlay(AActor* Object)
{
	Super::OnObjectBeginPlay(Object);
	if (Object != this)
	{
		return;
	}

}


void APumpkinField::OnObjectEndPlay(AActor* Object)
{
	Super::OnObjectEndPlay(Object);
	if (Object != this)
	{
		return;
	}



}

void APumpkinField::OnReduceHealth(float Damage, AActor* CauserActor)
{
	Super::OnReduceHealth(Damage, CauserActor);





}

void APumpkinField::OnAddHealth(float Heal, AActor* CauserActor)
{
	Super::OnAddHealth(Heal, CauserActor);



}



void APumpkinField::OnDied()
{
	Super::OnDied();

	if (this->Maturation < this->MaxMaturation)
	{
		UStaticMesh* Mesh = MeshArray[0];
		this->MeshComponent->SetStaticMesh(Mesh);
		this->MeshComponent->SetMaterial(0, Mesh->GetMaterial(0));
		this->HealthComponent->SetIsDeath(false);
		return;
	}
	auto Lambda = [this]()
		{
			this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectEnterPool.Broadcast(this, EObjectPoolType::PumpkinField);
		};
	GetWorld()->GetTimerManager().SetTimer(this->DelayTimer, Lambda, 1.0f, false);
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnVillagerCompleteJob.Broadcast(GetActorLocation());

}

