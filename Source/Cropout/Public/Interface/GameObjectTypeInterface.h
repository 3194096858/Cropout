// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Enum/GameObjectType/GameObjectType.h"



#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameObjectTypeInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGameObjectTypeInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CROPOUT_API IGameObjectTypeInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual EGameObjectType GetGameObjectType() = 0;
	virtual void SetGameObjectType(EGameObjectType NewType) = 0;

};
