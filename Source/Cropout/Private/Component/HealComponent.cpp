

#include "Component/HealComponent.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Component/CollisionDetectionComponent.h"

#include "Component/HealthComponent.h"

UHealComponent::UHealComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UHealComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UHealComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


void UHealComponent::ApplyHeal(const FVector& StartLocation, const FVector& EndLocation, UCollisionDetectionComponent* CollisionDetectionComponent, float Radius)
{
	if (CollisionDetectionComponent == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UHealComponent::ApplyHeal(): CollisionDetectionComponent == nullptr"));
		return;
	}
	CollisionDetectionComponent->CapsuleTraceForObject(StartLocation, EndLocation, Radius, Radius, this->HealObjectTypeQueryArray, true);
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
			UE_LOG(LogTemp, Warning, TEXT("UDamageComponent::ApplyHeal(): HealthComponent ==nullptr"));
			return;
		}
		HealthComponent->AddHealth(this->Heal, this->GetOwner());
		return;
	}
	for (auto& Element : CapsuleHitResultArray)
	{
		CollisionDetectionComponent->LineTraceForObject(GetOwner()->GetActorLocation(), Element.GetActor()->GetActorLocation(), this->HealObjectTypeQueryArray, true);
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
		UE_LOG(LogTemp, Warning, TEXT("UDamageComponent::ApplyHeal(): ObjectDistanceMap.FindKey(ObjectDistanceArray[0]) ==nullptr"));
		return;
	}
	TargetActor = *ObjectDistanceMap.FindKey(ObjectDistanceArray[0]);
	HealthComponent = TargetActor->GetComponentByClass<UHealthComponent>();
	if (HealthComponent == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("UDamageComponent::ApplyHeal(): HealthComponent ==nullptr"));
		return;
	}
	HealthComponent->AddHealth(this->Heal, this->GetOwner());

}


//
//float UDamageComponent::GetDamage()
//{
//	return this->Damage;
//}
//float UDamageComponent::GetHitSpeed()
//{
//	return this->HitSpeed;
//}
//float UDamageComponent::GetMaxDamage()
//{
//	return this->MaxDamage;
//}
//float UDamageComponent::GetMaxHitSpeed()
//{
//	return this->MaxHitSpeed;
//}
//void UDamageComponent::SetDamage(float NewDamage)
//{
//	this->Damage = NewDamage;
//}
//void UDamageComponent::SetHitSpeed(float NewHitSpeed)
//{
//	this->HitSpeed = NewHitSpeed;
//}
//void UDamageComponent::SetMaxDamage(float NewMaxDamage)
//{
//	this->MaxDamage = NewMaxDamage;
//}
//void UDamageComponent::SetMaxHitSpeed(float NewMaxHitSpeed)
//{
//	this->MaxHitSpeed = NewMaxHitSpeed;
//}
//
