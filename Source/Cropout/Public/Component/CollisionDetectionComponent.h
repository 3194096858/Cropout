
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CollisionDetectionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CROPOUT_API UCollisionDetectionComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	UCollisionDetectionComponent();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
//**************************变量
public:
	//UPROPERTY(EditAnywhere)
	//EDrawDebugTrace::Type DrawDebugTrace;

	UPROPERTY(EditAnywhere)
	bool IsDrawDebugTrace = false;

	UPROPERTY(EditAnywhere)
	bool IsUseDefaultObjectTypeQuery = true;

	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EObjectTypeQuery>> DefaultObjectTypeQueryArray;

private:
	TArray<FHitResult> HitResultArray;

	//**************************函数
public:
	UFUNCTION()
	TArray<FHitResult> GetHitResultArray();
   
    UFUNCTION()
	void LineTraceForObject(const FVector& StartLocation, const FVector& EndLocation, TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypeQueryArray = {}, bool IsIgnoreSelf = true);
	UFUNCTION()
	void SphereTraceForObject(const FVector& StartLocation, const FVector& EndLocation, float Radius, TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypeQueryArray = {}, bool IsIgnoreSelf = true);
	UFUNCTION()
	void BoxTraceForObject(const FVector& StartLocation, const FVector& EndLocation, const FVector& HalfSize, const FRotator& Orientation, TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypeQueryArray = {}, bool IsIgnoreSelf = true);
	UFUNCTION()
	void CapsuleTraceForObject(const FVector& StartLocation, const FVector& EndLocation, float Radius, float HalfHeight, TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypeQueryArray = {}, bool IsIgnoreSelf = true);
	UFUNCTION()
	FHitResult GetFirstHitResult();
	UFUNCTION()
	int32 GetHitResultNumber();


private:
	UFUNCTION()
	void ClearHitResultArray();
		
};
