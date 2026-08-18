

#include "VFX/VFX.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"
#include "Component/CollisionDetectionComponent.h"
#include "GameMode/CropoutGameMode.h"
#include "GameInstance/CropoutGameInstance.h"
#include "Manager/DelegateManager.h"
#include "Kismet/GameplayStatics.h"


AVFX::AVFX()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	this->MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	this->SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	this->CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComponent");
	this->CollisionDetectionComponent = CreateDefaultSubobject<UCollisionDetectionComponent>("CollisionDetectionComponent");
	SetRootComponent(this->SceneComponent);

	this->MeshComponent->SetupAttachment(this->SceneComponent);
	this->CapsuleComponent->SetupAttachment(this->SceneComponent);

	this->MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	this->MeshComponent->SetCastShadow(false);
	this->MeshComponent->bReceivesDecals = false;

}


void AVFX::BeginPlay()
{
	Super::BeginPlay();
	CropoutGameMode = Cast<ACropoutGameMode>(UGameplayStatics::GetGameMode(this));
	if (CropoutGameMode == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AVFX::BeginPlay(): CropoutGameMode == nullptr"));
		return;
	}
	auto Lambda = [this]()
		{
			if (CropoutGameMode->GetGameInstance() == nullptr)
			{
				UE_LOG(LogTemp, Error, TEXT("AVFX::BeginPlay(): CropoutGameMode->GetGameInstance() == nullptr"));
				return;
			}
			if (CropoutGameMode->GetGameInstance()->GetDelegateManager() == nullptr)
			{
				UE_LOG(LogTemp, Error, TEXT("AVFX::BeginPlay(): CropoutGameMode->GetGameInstance()->GetDelegateManager() == nullptr"));
				return;
			}
			this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectBeginPlay.AddUObject(this, &AVFX::OnObjectBeginPlay);
			this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectEndPlay.AddUObject(this, &AVFX::OnObjectEndPlay);
			this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnMouseMove.AddUObject(this, &AVFX::OnMouseMove);
			this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnMouseLeftKeyRelease.AddUObject(this, &AVFX::OnMouseLeftKeyRelease);

		};
	GetWorld()->GetTimerManager().SetTimer(this->InitializationTimer, Lambda, 1.0f, false);



}

void AVFX::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



UStaticMeshComponent* AVFX::GetMeshComponent()
{
	if(this->MeshComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AVFX::GetMeshComponent() : MeshComponent == nullptr"));
	}
	return this->MeshComponent;
}

void AVFX::OnObjectBeginPlay(AActor* Object)
{



}


void AVFX::OnObjectEndPlay(AActor* Object)
{



}



void AVFX::OnMouseMove(const FVector& MouseLocation)
{



}



void AVFX::OnMouseLeftKeyRelease()
{



}