
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealComponent.generated.h"


class UCollisionDetectionComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CROPOUT_API UHealComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	UHealComponent();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(EditAnywhere)
	TArray<TEnumAsByte<EObjectTypeQuery>> HealObjectTypeQueryArray;
private:
	float Heal = 10.0f;
	float MaxHeal = 100.0f;
	float HitSpeed = 10.0f;
	float MaxHitSpeed = 100.0f;
	float Range = 100.0f;
	float MaxRange = 100.0f;

public:
	UFUNCTION()
	void ApplyHeal(const FVector& StartLocation, const FVector& EndLocation, UCollisionDetectionComponent* CollisionDetectionComponent, float Radius = 100.0f);
	/*UFUNCTION()
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
	void SetMaxHitSpeed(float NewMaxHitSpeed);*/




};
