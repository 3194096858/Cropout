// Fill out your copyright notice in the Description page of Project Settings.


#include "GameObject/LettuceField.h"


#include "Component/HealthComponent.h"
#include "Manager/DecalManager.h"
#include "GameMode/CropoutGameMode.h"
#include "GameInstance/CropoutGameInstance.h"
#include "Manager/DelegateManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Component/CollisionDetectionComponent.h"


ALettuceField::ALettuceField()
{
	SetGameObjectType(EGameObjectType::LettuceField);
	SetMaxMaturation(5);
	SetRelatedObjectPoolType(EObjectPoolType::LettuceField);

}

void ALettuceField::BeginPlay()
{
	Super::BeginPlay();
	

}

void ALettuceField::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ALettuceField::OnObjectBeginPlay(AActor* Object)
{
	Super::OnObjectBeginPlay(Object);
	if (Object != this)
	{
		return;
	}

}


void ALettuceField::OnObjectEndPlay(AActor* Object)
{
	Super::OnObjectEndPlay(Object);
	if (Object != this)
	{
		return;
	}



}

void ALettuceField::OnReduceHealth(float Damage, AActor* CauserActor)
{
	Super::OnReduceHealth(Damage, CauserActor);





}

void ALettuceField::OnAddHealth(float Heal, AActor* CauserActor)
{
	Super::OnAddHealth(Heal, CauserActor);



}



void ALettuceField::OnDied()
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
			this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectEnterPool.Broadcast(this, EObjectPoolType::LettuceField);
		};
	GetWorld()->GetTimerManager().SetTimer(this->DelayTimer, Lambda, 1.0f, false);
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnVillagerCompleteJob.Broadcast(GetActorLocation());

}

