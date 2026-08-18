

#include "Component/HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UHealthComponent::ReduceHealth(float Damage, AActor* CauserActor)
{
	if (this->IsDeath == true)
	{
		return;
	}
	this->Health -= Damage;
	if (this->Health <= 0)
    {
        this->IsDeath = true;
		this->Health = 0.0f;
        OnDied.ExecuteIfBound();
    }
    OnReduceHealth.ExecuteIfBound(Damage, CauserActor);
    

	
}

void UHealthComponent::AddHealth(float Heal, AActor* CauserActor)
{
	if (this->IsDeath == true || this->Health >= this->MaxHealth)
	{
		return;
	}
	this->Health += Heal;
	OnAddHealth.ExecuteIfBound(Heal, CauserActor);
	if (this->Health > this->MaxHealth)
	{
		this->Health = this->MaxHealth;
	}


}

void UHealthComponent::ResetAllProperty()
{
	this->Health = this->MaxHealth;
	this->IsDeath = false;
}

void UHealthComponent::SetCurrentHealth(float NewHealth)
{
	this->Health = FMath::Clamp(NewHealth, 0.0f, this->MaxHealth);

}

void UHealthComponent::SetMaxHealth(float NewMaxHealth)
{
	this->MaxHealth = FMath::Clamp(NewMaxHealth,0.0f,9999.0f);
}

void UHealthComponent::SetIsDeath(bool NewBool)
{
	this->IsDeath = NewBool;
}

float UHealthComponent::GetCurrentHealth()
{
	return this->Health;
}

float UHealthComponent::GetHealthPercent()
{
	return this->Health / this->MaxHealth;
}

float UHealthComponent::GetMaxHealth()
{
	return this->MaxHealth;
}

bool UHealthComponent::GetIsDeath()
{
	return this->IsDeath;
}
