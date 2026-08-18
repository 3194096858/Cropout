
#pragma once

#include "CoreMinimal.h"
#include "GameObject/GameObject.h"
#include "Ground.generated.h"




class UBoxComponent;




UCLASS()
class CROPOUT_API AGround : public AGameObject
{
	GENERATED_BODY()

public:
	AGround();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;

public:



private:
    UPROPERTY(VisibleAnywhere)
    UBoxComponent* BoxComponent;

	virtual void OnGameStartInitialization() override;





};
