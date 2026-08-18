

#include "GameObject/CornField.h"
#include "Component/HealthComponent.h"
#include "Manager/DecalManager.h"
#include "GameMode/CropoutGameMode.h"
#include "GameInstance/CropoutGameInstance.h"
#include "Manager/DelegateManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Component/CollisionDetectionComponent.h"



ACornField::ACornField()
{
	SetGameObjectType(EGameObjectType::CornField);
	SetMaxMaturation(2);
	SetRelatedObjectPoolType(EObjectPoolType::CornField);

}

void ACornField::BeginPlay()
{
	Super::BeginPlay();
	

}

void ACornField::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void ACornField::OnObjectBeginPlay(AActor* Object)
{
	Super::OnObjectBeginPlay(Object);
	if (Object != this)
	{
		return;
	}
	
}


void ACornField::OnObjectEndPlay(AActor* Object)
{
	Super::OnObjectEndPlay(Object);
	if (Object != this)
	{
		return;
	}
	


}

void ACornField::OnReduceHealth(float Damage, AActor* CauserActor)
{
	Super::OnReduceHealth(Damage, CauserActor);





}

void ACornField::OnAddHealth(float Heal, AActor* CauserActor)
{
	Super::OnAddHealth(Heal, CauserActor);
	


}



void ACornField::OnDied()
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
			this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectEnterPool.Broadcast(this, EObjectPoolType::CornField);
		};
	GetWorld()->GetTimerManager().SetTimer(this->DelayTimer, Lambda, 1.0f, false);
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnVillagerCompleteJob.Broadcast(GetActorLocation());

}



