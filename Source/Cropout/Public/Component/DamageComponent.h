
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageComponent.generated.h"


class UCollisionDetectionComponent;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CROPOUT_API UDamageComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	UDamageComponent();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
public:
	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EObjectTypeQuery>> DamageObjectTypeQueryArray;
private:
	float Damage = 10.0f;
	float MaxDamage = 100.0f;
	float HitSpeed = 10.0f;
	float MaxHitSpeed = 100.0f;
	float Range = 100.0f;
    float MaxRange = 100.0f;
	//EDamageType DamageType;

public:
    UFUNCTION()
	void ApplyDamage(const FVector& StartLocation, const FVector& EndLocation,  UCollisionDetectionComponent* CollisionDetectionComponent ,float Radius = 100.0f);
	UFUNCTION()
	float GetDamage();
	UFUNCTION()
	float GetMaxDamage();
    UFUNCTION()
	float GetHitSpeed();
	UFUNCTION()
	float GetMaxHitSpeed();
    UFUNCTION()
	void SetDamage(float NewDamage);
	UFUNCTION()
	void SetMaxDamage(float NewMaxDamage);
    UFUNCTION()
	void SetHitSpeed(float NewHitSpeed);
	UFUNCTION()
	void SetMaxHitSpeed(float NewMaxHitSpeed);
	

private:
		
};
