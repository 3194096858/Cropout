

#include "ObjectPool/CropoutObjectPool.h"
#include "Components/BoxComponent.h"
#include "GameMode/CropoutGameMode.h"
#include "GameInstance/CropoutGameInstance.h"
#include "Manager/DelegateManager.h"
#include "Kismet/GameplayStatics.h"

ACropoutObjectPool::ACropoutObjectPool()
{
	PrimaryActorTick.bCanEverTick = false;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	SetRootComponent(SceneComponent);
    BoxComponent->SetupAttachment(SceneComponent);
    BoxComponent->SetBoxExtent(FVector(100.0f,100.0f,100.0f));



}

void ACropoutObjectPool::BeginPlay()
{
	Super::BeginPlay();
	if (IsInitialize == true)
	{
		Initialize();
	}
	this->CropoutGameMode = Cast<ACropoutGameMode>(UGameplayStatics::GetGameMode(this));
	if (this->CropoutGameMode == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ACropoutObjectPool::BeginPlay(): CropoutGameMode == nullptr"));
		return;
	}

	auto Lambda = [this]()
	{ 
		if (this->CropoutGameMode->GetGameInstance() == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("ACropoutObjectPool::BeginPlay(): CropoutGameMode->GetGameInstance() == nullptr"));
			return;
		}
		if (this->CropoutGameMode->GetGameInstance()->GetDelegateManager() == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("ACropoutObjectPool::BeginPlay(): CropoutGameMode->GetGameInstance()->GetDelegateManager() == nullptr"));
			return;
		}
		this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectLeavePool.AddUObject(this, &ACropoutObjectPool::OnObjectLeavePool);
		this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectEnterPool.AddUObject(this, &ACropoutObjectPool::OnObjectEnterPool);
		this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnMouseMove.AddUObject(this, &ACropoutObjectPool::OnMouseMove);
		this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnMouseLeftKeyRelease.AddUObject(this, &ACropoutObjectPool::OnMouseLeftKeyRelease);
		this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnMouseLeftKeyPress.AddUObject(this, &ACropoutObjectPool::OnMouseLeftKeyPress);

	};
	GetWorld()->GetTimerManager().SetTimer(this->InitializationTimer, Lambda, 1.0f, false);


}

void ACropoutObjectPool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACropoutObjectPool::ObjectBeginPlay(AActor* Object, const FTransform& ObjectTransform)
{
	bool* IsActive = nullptr;
	Object->SetActorHiddenInGame(false);
	Object->SetActorTickEnabled(true);
	Object->SetActorTransform(ObjectTransform);
	Object->SetActorEnableCollision(true);
	IsActive = this->ObjectMap.Find(Object);
	if(IsActive != nullptr)
	{
		*IsActive = true;
	}
	

}


void ACropoutObjectPool::ObjectEndPlay(AActor* Object)
{
	bool* IsActive = nullptr;
	Object->SetActorHiddenInGame(true);
	Object->SetActorTickEnabled(false);
	Object->SetActorLocation(FVector(0.0f,0.0f,1000.0f));
	Object->SetActorEnableCollision(false);
	IsActive = this->ObjectMap.Find(Object);
	if (IsActive != nullptr)
	{
		*IsActive = false;
	}

}



void ACropoutObjectPool::Initialize()
{
	AActor* Object = nullptr;
	FTransform Transform = FTransform();
	Transform.SetLocation(FVector(0.0f, 0.0f, -1000.0f));
	Transform.SetRotation(FQuat(0.0f));
	Transform.SetScale3D(FVector(1.0f));
	if(this->ObjectClass == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACropoutObjectPool::Initialize(): ObjectClass == nullptr"));
		return;
	}
	for (int i = 0; i < this->PoolSize; i++)
	{
		Object = GetWorld()->SpawnActor<AActor>(this->ObjectClass, Transform);
		if (Object == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("ACropoutObjectPool::Initialize(): Object == nullptr"));
			return;
		}
		this->ObjectMap.Add(Object,false);
		ObjectEndPlay(Object);

	}




}


bool ACropoutObjectPool::CheckObjectPoolIsEmpty()
{
	for (auto& Element : ObjectMap)
	{
		if (Element.Key == nullptr)
		{
			continue;
		}
		if (Element.Value == false)
		{
			return false;
		}
	}
    return true;
}

TArray<AActor*> ACropoutObjectPool::GetAllActiveObject()
{
    TArray<AActor*> Array;
    for (auto& Element : ObjectMap)
    {
        if (Element.Key == nullptr)
        {
            UE_LOG(LogTemp, Warning, TEXT("ACropoutObjectPool::GetAllActiveObject(): Element.Key == nullptr"));
            return Array;
        }
        if (Element.Value == true)
        {
            Array.Add(Element.Key);
        }
    }
	return Array;
}

AActor* ACropoutObjectPool::GetRandomObjectFromPool()
{
	AActor* Object = nullptr;
	if (this->ObjectMap.FindKey(false) == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACropoutObjectPool::GetObjectFromPool(): ObjectMap.FindKey(false) == nullptr"));
		return Object;
	}
	Object = *this->ObjectMap.FindKey(false);
	return Object;
}


AActor* ACropoutObjectPool::GetObjectByName(const FName& ObjectName)
{
	AActor* Object = nullptr;
	for(auto& Element : this->ObjectMap)
	{
		if (FName(Element.Key->GetName()) == ObjectName)
		{
			Object = Element.Key;
			break;
		}
	}
	return Object;
}

AActor* ACropoutObjectPool::GetTargetObjectFromPool(AActor* TargetObject)
{
	if (this->ObjectMap.Find(TargetObject) == nullptr)
	{
		return nullptr;
	}
	if(*this->ObjectMap.Find(TargetObject)==true)
	{
		return nullptr;
	}
	return TargetObject;
}


bool ACropoutObjectPool::CheckObjectIsActive(AActor* Object)
{
	bool IsActive = false;
	if (this->ObjectMap.Find(Object) == nullptr)
	{
		return IsActive;
	}
    IsActive = *this->ObjectMap.Find(Object);
	return IsActive;
}


int ACropoutObjectPool::GetActiveObjectNumber()
{
	int Number = 0;
	for (auto& Element : ObjectMap)
	{
		if (Element.Key == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("ACropoutObjectPool::GetNumberOfUseObject(): Element == nullptr"));
			return -1;
		}
		if (Element.Value == true)
		{
			Number++;
		}
	}
	return Number;

}

void ACropoutObjectPool::SetObjectPoolType(EObjectPoolType NewType)
{ 
	this->ObjectPoolType = NewType;
}

TMap<AActor*,bool>& ACropoutObjectPool::GetObjectMap()
{
	return this->ObjectMap;
}

ACropoutGameMode* ACropoutObjectPool::GetGameMode()
{
	return this->CropoutGameMode;
}


void ACropoutObjectPool::OnObjectLeavePool(AActor* Object,const FTransform& ObjectTransform, EObjectPoolType TargetObjectPoolType)
{
    if (TargetObjectPoolType != this->ObjectPoolType)
    {
        return;
    }
	if (Object != nullptr && ObjectMap.Find(Object) == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACropoutObjectPool::OnObjectLeavePool(): Object != nullptr && ObjectMap.Find(Object) == nullptr"));
		return;
	}
	if(Object == nullptr)
	{
		Object = GetRandomObjectFromPool();
		if (Object == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("ACropoutObjectPool::OnObjectLeavePool(): Object == nullptr"));
			return;
		}
	}
    ObjectBeginPlay(Object,ObjectTransform);
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectBeginPlay.Broadcast(Object);
	
}

void ACropoutObjectPool::OnObjectEnterPool(AActor* Object, EObjectPoolType TargetObjectPoolType)
{
	if (TargetObjectPoolType != this->ObjectPoolType)
	{
		return;
	}
	if (Object == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACropoutObjectPool::OnObjectEnterPool(): Object == nullptr"));
		return;
	}
	if (ObjectMap.Find(Object) == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("ACropoutObjectPool::OnObjectEnterPool(): ObjectMap.Find(Object) == nullptr"));
	}
	ObjectEndPlay(Object);
	this->CropoutGameMode->GetGameInstance()->GetDelegateManager()->OnObjectEndPlay.Broadcast(Object);

}


void ACropoutObjectPool::OnMouseLeftKeyPress(const FVector& MouseLocation)
{

}



void ACropoutObjectPool::OnMouseMove(const FVector& MouseLocation)
{ 
}


void ACropoutObjectPool::OnMouseLeftKeyRelease()
{

}



void ACropoutObjectPool::OnGameInitializationComplete()
{

	
}


