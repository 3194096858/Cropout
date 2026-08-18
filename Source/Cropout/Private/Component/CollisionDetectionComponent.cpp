#include "Component/CollisionDetectionComponent.h"
#include "Kismet/KismetSystemLibrary.h"





UCollisionDetectionComponent::UCollisionDetectionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UCollisionDetectionComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UCollisionDetectionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}



TArray<FHitResult> UCollisionDetectionComponent::GetHitResultArray()
{
	return this->HitResultArray;
}

FHitResult UCollisionDetectionComponent::GetFirstHitResult()
{
    if (this->HitResultArray.Num() == 0)
    {
        return FHitResult();
    }
    return this->HitResultArray[0];
}


int32 UCollisionDetectionComponent::GetHitResultNumber()
{
	return this->HitResultArray.Num();
}


void UCollisionDetectionComponent::ClearHitResultArray()
{
	if (this->HitResultArray.Num() == 0)
	{
		return;
	};
	this->HitResultArray.Empty();
};


void UCollisionDetectionComponent::LineTraceForObject(const FVector& StartLocation, const FVector& EndLocation, TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypeQueryArray, bool IsIgnoreSelf)
{
	TArray<AActor*> IgnoreActorArray;
	EDrawDebugTrace::Type DrawDebugTrace = EDrawDebugTrace::None;
	TArray<TEnumAsByte<EObjectTypeQuery>> TypeQueryArray = ObjectTypeQueryArray;
	if (this->IsDrawDebugTrace == true)
	{
		DrawDebugTrace = EDrawDebugTrace::ForDuration;
	}
	if (this->IsUseDefaultObjectTypeQuery == true)
	{
		//TypeQueryArray = this->ObjectTypeQueryArray;
		TypeQueryArray = this->DefaultObjectTypeQueryArray;

	}
	if (TypeQueryArray.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("UCollisionDetectionComponent::LineTraceForObject(): TypeQueryArray.Num()==0"));
		return;
	}
	ClearHitResultArray();
	UKismetSystemLibrary::LineTraceMultiForObjects(this, StartLocation, EndLocation, TypeQueryArray, false, IgnoreActorArray, DrawDebugTrace, this->HitResultArray, IsIgnoreSelf);




}


void UCollisionDetectionComponent::SphereTraceForObject(const FVector& StartLocation, const FVector& EndLocation, float Radius, TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypeQueryArray, bool IsIgnoreSelf)
{
	TArray<AActor*> IgnoreActorArray;
	EDrawDebugTrace::Type DrawDebugTrace = EDrawDebugTrace::None;
	TArray<TEnumAsByte<EObjectTypeQuery>> TypeQueryArray = ObjectTypeQueryArray;
	if (this->IsDrawDebugTrace == true)
	{
		DrawDebugTrace = EDrawDebugTrace::ForDuration;
	}
	if (this->IsUseDefaultObjectTypeQuery == true)
	{
		//TypeQueryArray = this->ObjectTypeQueryArray;
		TypeQueryArray = this->DefaultObjectTypeQueryArray;

	}
	if (TypeQueryArray.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("UCollisionDetectionComponent::SphereTraceForObject(): TypeQueryArray.Num()==0"));
		return;
	}
	ClearHitResultArray();
	UKismetSystemLibrary::SphereTraceMultiForObjects(this, StartLocation, EndLocation, Radius, TypeQueryArray, false, IgnoreActorArray, DrawDebugTrace, this->HitResultArray, IsIgnoreSelf);




}


void UCollisionDetectionComponent::BoxTraceForObject(const FVector& StartLocation, const FVector& EndLocation, const FVector& HalfSize, const FRotator& Orientation, TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypeQueryArray, bool IsIgnoreSelf)
{
	TArray<AActor*> IgnoreActorArray;
	EDrawDebugTrace::Type DrawDebugTrace = EDrawDebugTrace::None;
	TArray<TEnumAsByte<EObjectTypeQuery>> TypeQueryArray = ObjectTypeQueryArray;
	if (this->IsDrawDebugTrace == true)
	{
		DrawDebugTrace = EDrawDebugTrace::ForDuration;
	}
	if (this->IsUseDefaultObjectTypeQuery == true)
	{
		TypeQueryArray = this->DefaultObjectTypeQueryArray;

	}
	if (TypeQueryArray.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("UCollisionDetectionComponent::BoxTraceForObject(): TypeQueryArray.Num()==0"));
		return;
	}
	ClearHitResultArray();
	UKismetSystemLibrary::BoxTraceMultiForObjects(this, StartLocation, EndLocation, HalfSize, Orientation, TypeQueryArray, false, IgnoreActorArray, DrawDebugTrace, this->HitResultArray, IsIgnoreSelf);




}




void UCollisionDetectionComponent::CapsuleTraceForObject(const FVector& StartLocation, const FVector& EndLocation, float Radius, float HalfHeight, TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypeQueryArray, bool IsIgnoreSelf)
{
	TArray<AActor*> IgnoreActorArray;
	EDrawDebugTrace::Type DrawDebugTrace = EDrawDebugTrace::None;
	TArray<TEnumAsByte<EObjectTypeQuery>> TypeQueryArray = ObjectTypeQueryArray;
	if (this->IsDrawDebugTrace == true)
	{
		DrawDebugTrace = EDrawDebugTrace::ForDuration;
	}
	if (this->IsUseDefaultObjectTypeQuery == true)
	{
		TypeQueryArray = this->DefaultObjectTypeQueryArray;

	}
	if (TypeQueryArray.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("UCollisionDetectionComponent::CapsuleTraceForObject(): TypeQueryArray.Num()==0"));
		return;
	}
	ClearHitResultArray();
	UKismetSystemLibrary::CapsuleTraceMultiForObjects(this, StartLocation, EndLocation, Radius, HalfHeight, TypeQueryArray, false, IgnoreActorArray, DrawDebugTrace, this->HitResultArray, IsIgnoreSelf);




}


