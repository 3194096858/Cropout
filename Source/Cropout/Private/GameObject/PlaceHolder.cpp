

#include "GameObject/PlaceHolder.h"


#include "Component/CollisionDetectionComponent.h"

#include "Enum/ObjectPoolType.h"
#include "Components/TimelineComponent.h"
#include "GameMode/CropoutGameMode.h"
#include "GameInstance/CropoutGameInstance.h"
#include "Manager/DelegateManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Manager/WidgetManager.h"
#include "Manager/DataManager.h"

APlaceHolder::APlaceHolder()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	this->TimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineComponent"));
	this->PlacementVFXMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlacementVFXMesh"));
	this->CircleRingVFXMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CircleRingVFXMesh"));
	this->PlacementVFXMesh->SetupAttachment(this->SceneComponent);
	this->CircleRingVFXMesh->SetupAttachment(this->SceneComponent);
	SetRelatedObjectPoolType(EObjectPoolType::PlaceHolder);
	SetGameObjectType(EGameObjectType::PlaceHolder);
	this->PlacementVFXMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	this->CircleRingVFXMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	this->PlacementVFXMesh->bReceivesDecals = false;
	this->CircleRingVFXMesh->bReceivesDecals = false;
	this->CircleRingVFXMesh->SetRelativeScale3D(FVector(6.0f));
	this->PlacementVFXMesh->SetRelativeScale3D(FVector(5.0f,5.0f,10.0f));
	this->CircleRingVFXMesh->SetRelativeLocation(FVector(0.0f,0.0f,3.0f));
	this->PlacementVFXMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 510.0f));
	this->CapsuleComponent->SetCapsuleSize(300.0f, 300.0f);
	this->CapsuleComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f));

}

void APlaceHolder::BeginPlay()
{
	Super::BeginPlay();
	InitializeMinFloatingSizeMap();
	InitializeAnimation();
	auto Lambda = [this]()
		{
			if (CropoutGameMode->GetGameInstance() == nullptr)
			{
				UE_LOG(LogTemp, Error, TEXT("AGameObject::BeginPlay(): CropoutGameMode->GetGameInstance() == nullptr"));
				return;
			}
			if (CropoutGameMode->GetGameInstance()->GetDelegateManager() == nullptr)
			{
				UE_LOG(LogTemp, Error, TEXT("AGameObject::BeginPlay(): CropoutGameMode->GetGameInstance()->GetDelegateManager() == nullptr"));
				return;
			}
			this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameWin.AddUObject(this, &APlaceHolder::OnGameWin);
			this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnGameOver.AddUObject(this, &APlaceHolder::OnGameOver);
			this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnPlayerCloseCardOperationPanel.AddUObject(this, &APlaceHolder::OnPlayerCloseCardOperationPanel);
			this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnPlayerRotateGameObject.AddUObject(this, &APlaceHolder::OnPlayerRotateGameObject);
			this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnPlayerSelectCard.AddUObject(this, &APlaceHolder::OnPlayerSelectCard);
			this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnPlayerPlaceGameObject.AddUObject(this, &APlaceHolder::OnPlayerPlaceGameObject);
			this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnMouseMove.AddUObject(this,&APlaceHolder::OnMouseMove);
		};
	GetWorld()->GetTimerManager().SetTimer(this->InitializationTimer, Lambda, 1.0f, false);
	
}

void APlaceHolder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	float Radious = this->CapsuleComponent->GetUnscaledCapsuleRadius();
	FName ParameterName = FName("CanPlace");
	float Value = 1.0f;
	FVector2D Position;
	UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(PlayerController, GetActorLocation(), Position, false);
	this->CropoutGameMode->GetGameInstance()->GetWidgetManager()->UpdateCardOperationPanelPosition(Position);
	this->CollisionDetectionComponent->SphereTraceForObject(GetActorLocation(), GetActorLocation(), Radious);
	if (this->CollisionDetectionComponent->GetHitResultNumber() == 0)
	{
		this->CanPlace = true;
		this->PlacementVFXMesh->SetScalarParameterValueOnMaterials(ParameterName, Value);
	}
	else
	{
		this->CanPlace = false;
		Value = 0.0f;
		this->PlacementVFXMesh->SetScalarParameterValueOnMaterials(ParameterName, Value);

	}

}



void APlaceHolder::InitializeAnimation()
{
	if (this->Curve_010 == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("APlaceHolder::InitializeAnimation(): this->Curve_010 == nullptr"));
		return;
	}
	FOnTimelineFloatStatic Delegate;
	Delegate.BindUObject(this, &APlaceHolder::SetFloatingAnimation);
	this->TimelineComponent->AddInterpFloat(this->Curve_010, Delegate);
	
}



void APlaceHolder::InitializeMinFloatingSizeMap()
{
	this->FloatingMinScaleMap.Add(EGameObjectType::Tree, 5.0f);
	this->FloatingMinScaleMap.Add(EGameObjectType::Stone, 5.0f);
	this->FloatingMinScaleMap.Add(EGameObjectType::Shrub, 4.0f);
	this->FloatingMinScaleMap.Add(EGameObjectType::TownHall, 10.0f);
	this->FloatingMinScaleMap.Add(EGameObjectType::VillagerHouse, 6.0f);
	this->FloatingMinScaleMap.Add(EGameObjectType::CornField, 7.0f);
	this->FloatingMinScaleMap.Add(EGameObjectType::WheatField, 7.0f);
	this->FloatingMinScaleMap.Add(EGameObjectType::PumpkinField, 7.0f);
	this->FloatingMinScaleMap.Add(EGameObjectType::LettuceField, 7.0f);
	this->FloatingMinScaleMap.Add(EGameObjectType::Monument, 12.0f);

}
//
//void APlaceHolder::InitializeGameObjectMeshMap()
//{
//
//
//
//}


void APlaceHolder::PlayAnimation(UTimelineComponent* Timeline, bool IsPlayFromStart, bool IsLooping, float PlayRate)
{
	Timeline->SetLooping(IsLooping);
	Timeline->SetPlayRate(PlayRate);
	IsPlayFromStart == true ? Timeline->PlayFromStart() : Timeline->ReverseFromEnd();

}

void APlaceHolder::SetFloatingAnimation(float Value)
{
	FVector NewScale;
	NewScale = FMath::Lerp(this->FloatingStartScale, this->FloatingEndScale, Value);
	this->CircleRingVFXMesh->SetWorldScale3D(NewScale);
}


void APlaceHolder::UpdateGameObjectMesh(const FName& ObjectName)
{
	if (this->CropoutGameMode->CheckActorIsActive(this, EObjectPoolType::PlaceHolder) == false)
	{
		return;
	}
	UStaticMesh* Mesh = nullptr;
	UEnum* Enum = StaticEnum<EGameObjectType>();
	EGameObjectType ObjectType = EGameObjectType::None;
	int32 EnumIndex = Enum->GetIndexByName(ObjectName);
	ObjectType = static_cast<EGameObjectType>(Enum->GetValueByIndex(EnumIndex));
	if (ObjectType == EGameObjectType::None)
	{
		return;
	}
	if (this->GameObjectMeshMap.Find(ObjectType) == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("APlaceHolder::OnPlayerSelectCard(): this->GameObjectMeshMap.Find(ObjectType) == nullptr"));
		return;
	}
	Mesh = *this->GameObjectMeshMap.Find(ObjectType);
	this->MeshComponent->SetStaticMesh(Mesh);

}


void APlaceHolder::OnObjectBeginPlay(AActor* Object)
{
	if (Object != this)
	{
		return;
	}
	UpdateGameObjectMesh(this->SelectedObjectName);
	this->MeshComponent->SetRelativeRotation(FRotator(0.0f,45.0f,0.0f));
	this->PlacementVFXMesh->SetRelativeRotation(FRotator(0.0f, 45.0f, 0.0f));
	UEnum* Enum = StaticEnum<EGameObjectType>();
	EGameObjectType ObjectType = EGameObjectType::None;
	int32 EnumIndex = Enum->GetIndexByName(this->SelectedObjectName);
	ObjectType = static_cast<EGameObjectType>(Enum->GetValueByIndex(EnumIndex));
	if (ObjectType == EGameObjectType::None)
	{
		return;
	}
	if(ObjectType == EGameObjectType::Monument)
	{
		this->CapsuleComponent->SetCapsuleSize(600.0f,600.0f);
		this->PlacementVFXMesh->SetWorldScale3D(FVector(12.0f,12.0f,10.0f));
	}
	if (this->FloatingMinScaleMap.Find(ObjectType) == nullptr)
	{
        UE_LOG(LogTemp, Error, TEXT("APlaceHolder::OnObjectBeginPlay(): ObjectType == EGameObjectType::None"));
		return;
	}
	this->FloatingStartScale = FVector(*this->FloatingMinScaleMap.Find(ObjectType));
	this->FloatingEndScale = FVector(*this->FloatingMinScaleMap.Find(ObjectType)) * this->FloatingAmplitude;
	PlayAnimation(this->TimelineComponent,true,true);


}


void APlaceHolder::OnObjectEndPlay(AActor* Object)
{
	if (Object != this)
	{
		return;
	}
	this->MeshComponent->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	this->PlacementVFXMesh->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	this->TimelineComponent->Stop();
	this->PlacementVFXMesh->SetWorldScale3D(FVector(5.0,5.0,10.0f));
	this->CapsuleComponent->SetCapsuleSize(300.0f, 300.0f);


}


void APlaceHolder::OnPlayerSelectCard(const FCardInformation& SelectedCard)
{
	this->SelectedObjectName = SelectedCard.Name;
	if (this->CropoutGameMode->CheckActorIsActive(this, EObjectPoolType::PlaceHolder) == false)
	{
		return;
	}
	

}




void APlaceHolder::OnPlayerPlaceGameObject(const FCardInformation& SelectedCard)
{
	if (this->CropoutGameMode->CheckActorIsActive(this, EObjectPoolType::PlaceHolder) == false)
	{
		return;
	}
	if (this->CanPlace == false)
	{
		this->CropoutGameMode->GetGameInstance()->GetWidgetManager()->AddPlacementTipToViewport();
		return;
	}
	FTransform Transform;
	FPlayerData PlayerData;
	UEnum* Enum = StaticEnum<EObjectPoolType>();
	EObjectPoolType PoolType = EObjectPoolType::None;
	int32 EnumIndex = Enum->GetIndexByName(SelectedCard.Name);
	PoolType = static_cast<EObjectPoolType>(Enum->GetValueByIndex(EnumIndex));
	if (PoolType == EObjectPoolType::None)
	{
		return;
	}
	if (this->CropoutGameMode->CheckObjectPoolIsEmpty(PoolType) == true)
	{
		UE_LOG(LogTemp, Warning, TEXT(" PlaceHolder : No Object !!!!"));
		this->CropoutGameMode->GetGameInstance()->GetWidgetManager()->AddObjectCountTipToViewport();
		return;
	}
	Transform.SetLocation(GetActorLocation());
	Transform.SetRotation(this->MeshComponent->GetRelativeRotation().Quaternion());
	PlayerData = this->CropoutGameMode->GetGameInstance()->GetDataManager()->GetPlayerData();
	for(auto& Element : PlayerData.ResourceMap)
	{
		if ( Element.Value < *SelectedCard.CostMap.Find(Element.Key))
		{
			UE_LOG(LogTemp, Warning, TEXT(" PlaceHolder : Player Haven't enough Resource !!!!"));
			//this->CanPlace = false;
			this->CropoutGameMode->GetGameInstance()->GetWidgetManager()->AddResourceTipToViewport();
			return;
		}
	}
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectLeavePool.Broadcast(nullptr, Transform, PoolType);
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnPlayerResourceReduce.Broadcast(SelectedCard.CostMap);


}

void APlaceHolder::OnPlayerRotateGameObject()
{
	if (this->CropoutGameMode->CheckActorIsActive(this, EObjectPoolType::PlaceHolder) == false)
	{
		return;
	}
	this->MeshComponent->SetRelativeRotation(this->MeshComponent->GetRelativeRotation() + FRotator(0.0f, 45.0f, 0.0f));

}


void APlaceHolder::OnPlayerCloseCardOperationPanel()
{
	if (this->CropoutGameMode->CheckActorIsActive(this, EObjectPoolType::PlaceHolder) == false)
	{
		return;
	}
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectEnterPool.Broadcast(this, EObjectPoolType::PlaceHolder);

}



void APlaceHolder::OnGameOver()
{
	if (this->CropoutGameMode->CheckActorIsActive(this, EObjectPoolType::PlaceHolder) == false)
	{
		return;
	}
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectEnterPool.Broadcast(this, EObjectPoolType::PlaceHolder);

}

void APlaceHolder::OnGameWin()
{
	if (this->CropoutGameMode->CheckActorIsActive(this, EObjectPoolType::PlaceHolder) == false)
	{
		return;
	}
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectEnterPool.Broadcast(this, EObjectPoolType::PlaceHolder);

}

void APlaceHolder::OnMouseMove(const FVector& MouseLocation)
{
	if (this->CropoutGameMode->CheckActorIsActive(this, EObjectPoolType::PlaceHolder) == false)
	{
		return;
	}
	FVector NewLocation = MouseLocation;
	SetActorLocation(NewLocation);


}




















