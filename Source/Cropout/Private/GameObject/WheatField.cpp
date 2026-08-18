

#include "GameObject/WheatField.h"


#include "Component/HealthComponent.h"
#include "Manager/DecalManager.h"
#include "GameMode/CropoutGameMode.h"
#include "GameInstance/CropoutGameInstance.h"
#include "Manager/DelegateManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Component/CollisionDetectionComponent.h"


AWheatField::AWheatField()
{
	SetGameObjectType(EGameObjectType::WheatField);
	SetMaxMaturation(3);
	SetRelatedObjectPoolType(EObjectPoolType::WheatField);

}

void AWheatField::BeginPlay()
{
	Super::BeginPlay();


}

void AWheatField::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AWheatField::OnObjectBeginPlay(AActor* Object)
{
	Super::OnObjectBeginPlay(Object);
	if (Object != this)
	{
		return;
	}

}


void AWheatField::OnObjectEndPlay(AActor* Object)
{
	Super::OnObjectEndPlay(Object);
	if (Object != this)
	{
		return;
	}



}

void AWheatField::OnReduceHealth(float Damage, AActor* CauserActor)
{
	Super::OnReduceHealth(Damage, CauserActor);





}

void AWheatField::OnAddHealth(float Heal, AActor* CauserActor)
{
	Super::OnAddHealth(Heal, CauserActor);



}



void AWheatField::OnDied()
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
			this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectEnterPool.Broadcast(this, EObjectPoolType::WheatField);
		};
	GetWorld()->GetTimerManager().SetTimer(this->DelayTimer, Lambda, 1.0f, false);
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnVillagerCompleteJob.Broadcast(GetActorLocation());

}

