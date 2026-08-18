
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DELEGATE_TwoParams(FOnAddHealth, float, AActor*);
DECLARE_DELEGATE_TwoParams(FOnReduceHealth, float, AActor*);
DECLARE_DELEGATE(FOnDied);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CROPOUT_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	UHealthComponent();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	//************************变量
public:
	FOnAddHealth OnAddHealth;
    FOnReduceHealth OnReduceHealth;
	FOnDied OnDied;

private:
	float Health = 100.0f;
    float MaxHealth = 100.0f;
	bool IsDeath = false;


	//****************************函数
public:
	UFUNCTION()
	float GetCurrentHealth();
    UFUNCTION()
	float GetHealthPercent();
    UFUNCTION()
	float GetMaxHealth();
    UFUNCTION()
	bool GetIsDeath();
	void SetCurrentHealth(float NewHealth);
	UFUNCTION()
	void SetMaxHealth(float NewMaxHealth);
    UFUNCTION()
	void SetIsDeath(bool NewBool);
    UFUNCTION()
	void ReduceHealth(float Damage, AActor* CauserActor);
    UFUNCTION()
	void AddHealth(float Heal, AActor* CauserActor);
	UFUNCTION()
	void ResetAllProperty();


private:

		
};
