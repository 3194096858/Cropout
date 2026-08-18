// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Enum/NPCState/NPCState.h"

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "NPCStateInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UNPCStateInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CROPOUT_API INPCStateInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual ENPCState GetNPCState() = 0;
	virtual void UpdateNPCState(ENPCState NewState) = 0;


};
