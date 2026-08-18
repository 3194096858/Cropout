

#include "GameObject/Ground/Ground.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "GameMode/CropoutGameMode.h"
#include "GameInstance/CropoutGameInstance.h"
#include "Manager/DelegateManager.h"
#include "Kismet/GameplayStatics.h"

AGround::AGround()
{

	PrimaryActorTick.bCanEverTick = false;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));


	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetGameObjectType(EGameObjectType::Ground);

	this->MeshComponent->bReceivesDecals = true;
	
}



void AGround::BeginPlay()
{
	Super::BeginPlay(); 
	this->BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	this->BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

}

void AGround::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGround::OnGameStartInitialization()
{
	//Super::OnGameStart();
	

}










