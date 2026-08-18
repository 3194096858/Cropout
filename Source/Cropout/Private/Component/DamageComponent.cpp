

#include "Component/DamageComponent.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Component/CollisionDetectionComponent.h"

#include "Component/HealthComponent.h"

UDamageComponent::UDamageComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UDamageComponent::BeginPlay()
{
	Super::BeginPlay();

	//AGameState
}


void UDamageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


void UDamageComponent::ApplyDamage(const FVector& StartLocation, const FVector& EndLocation, UCollisionDetectionComponent* CollisionDetectionComponent ,float Radius)
{
	if (CollisionDetectionComponent == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UDamageComponent::ApplyDamage(): CollisionDetectionComponent == nullptr"));
		return;
	}
	CollisionDetectionComponent->CapsuleTraceForObject(StartLocation, EndLocation, Radius, Radius, this->DamageObjectTypeQueryArray, true);
	if (CollisionDetectionComponent->GetHitResultNumber() == 0)
	{
		return;
	}
	AActor* TargetActor = nullptr;
	TArray<FHitResult> CapsuleHitResultArray;
	FHitResult LineHitResult;
	TArray<float> ObjectDistanceArray;
	TMap<AActor*, float> ObjectDistanceMap;
	UHealthComponent* HealthComponent = nullptr;
	CapsuleHitResultArray = CollisionDetectionComponent->GetHitResultArray();
	if (CapsuleHitResultArray.Num() == 1)
	{
		TargetActor = CapsuleHitResultArray[0].GetActor();
		HealthComponent = TargetActor->GetComponentByClass<UHealthComponent>();
		if (HealthComponent == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("UDamageComponent::ApplyDamage(): HealthComponent ==nullptr"));
			return;
		}
		HealthComponent->ReduceHealth(this->Damage, this->GetOwner());
		return;
	}
	for (auto& Element : CapsuleHitResultArray)
	{
		CollisionDetectionComponent->LineTraceForObject(GetOwner()->GetActorLocation(), Element.GetActor()->GetActorLocation(), this->DamageObjectTypeQueryArray, true);
		if (CollisionDetectionComponent->GetHitResultNumber() == 0)
		{
			continue;
		}
		LineHitResult = CollisionDetectionComponent->GetFirstHitResult();
		ObjectDistanceMap.Add(Element.GetActor(), LineHitResult.Distance);
		ObjectDistanceArray.Add(LineHitResult.Distance);
	}
	ObjectDistanceArray.Sort();
	if (ObjectDistanceMap.FindKey(ObjectDistanceArray[0]) == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UDamageComponent::ApplyDamage(): ObjectDistanceMap.FindKey(ObjectDistanceArray[0]) ==nullptr"));
		return;
	}
	TargetActor = *ObjectDistanceMap.FindKey(ObjectDistanceArray[0]);
	HealthComponent = TargetActor->GetComponentByClass<UHealthComponent>();
	if (HealthComponent == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UDamageComponent::ApplyDamage(): HealthComponent ==nullptr"));
		return;
	}
	HealthComponent->ReduceHealth(this->Damage, this->GetOwner());
}

float UDamageComponent::GetDamage()
{
	return this->Damage;
}
float UDamageComponent::GetHitSpeed()
{
	return this->HitSpeed;
}
float UDamageComponent::GetMaxDamage()
{
	return this->MaxDamage;
}
float UDamageComponent::GetMaxHitSpeed()
{
	return this->MaxHitSpeed;
}
void UDamageComponent::SetDamage(float NewDamage)
{
	this->Damage = NewDamage;
}
void UDamageComponent::SetHitSpeed(float NewHitSpeed)
{
	this->HitSpeed = NewHitSpeed;
}
void UDamageComponent::SetMaxDamage(float NewMaxDamage)
{
	this->MaxDamage = NewMaxDamage;
}
void UDamageComponent::SetMaxHitSpeed(float NewMaxHitSpeed)
{
	this->MaxHitSpeed = NewMaxHitSpeed;
}

