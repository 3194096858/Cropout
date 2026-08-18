// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/Villager.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Manager/DataManager.h"
#include "Component/CollisionDetectionComponent.h"
#include "GameMode/CropoutGameMode.h"
#include "GameInstance/CropoutGameInstance.h"
#include "Manager/DelegateManager.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/WidgetManager.h"
#include "Blueprint/WidgetLayoutLibrary.h"

AVillager::AVillager()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	GetCharacterMovement()->GravityScale = 0.0f;


}

void AVillager::BeginPlay()
{
	Super::BeginPlay();
	

}

void AVillager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//FVector2D Position;
	//APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	//UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(PlayerController, FVector(GetActorLocation().X, GetActorLocation().Y, 0.0f), Position, false);
	//this->CropoutGameMode->GetGameInstance()->GetWidgetManager()->UpdateDamageTextPosition(FName(this->GetName()), Position);

}


void AVillager::Attack()
{
	Super::Attack();

}


void AVillager::OnObjectBeginPlay(AActor* Object)
{
	Super::OnObjectBeginPlay(Object);
	if (Object != this)
	{
		return;
	}
	if (this->CropoutGameMode->GetGameInstance()->GetDataManager()->CheckVillagerDataIsExist(FName(GetName())) == false)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Create Data"));

		this->CropoutGameMode->GetGameInstance()->GetDataManager()->CreateVillagerData(FName(this->GetName()));
	}
	this->CropoutGameMode->GetGameInstance()->GetWidgetManager()->BindDamageText(this->CropoutGameMode->GetGameInstance(), this->CropoutGameMode->GetTextBlockWidgetClass(), FName(this->GetName()));
	GetCharacterMovement()->GravityScale = 1.0f;


}


void AVillager::OnObjectEndPlay(AActor* Object)
{
	Super::OnObjectEndPlay(Object);
	if (Object != this)
	{
		return;
	}
	this->CropoutGameMode->GetGameInstance()->GetDataManager()->DeleteVillagerData(FName(this->GetName()));
	this->CropoutGameMode->GetGameInstance()->GetWidgetManager()->UnbindDamageText(FName(this->GetName()));
	if(this->HatMeshComponent->IsVisible() == true)
	{
		RemoveHat();
	}
	if (this->WeaponMeshComponent->IsVisible() == true)
	{
		RemoveWeapon();
	}
	if (this->CrateMeshComponent->IsVisible() == true)
	{
		RemoveCrate();
	}
	
	GetCharacterMovement()->GravityScale = 0.0f;

}




void AVillager::OnPlayerReturnStartMenu()
{
	Super::OnPlayerReturnStartMenu();
	if (this->CropoutGameMode->CheckActorIsActive(this, EObjectPoolType::Villager) == false)
	{
		return;
	}
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectEnterPool.Broadcast(this, EObjectPoolType::Villager);


}
