// Fill out your copyright notice in the Description page of Project Settings.


#include "GameObject/Grass.h"


AGrass::AGrass()
{
	SetGameObjectType(EGameObjectType::Grass);
	SetRelatedObjectPoolType(EObjectPoolType::Grass);

}

void AGrass::BeginPlay()
{
	Super::BeginPlay();



}

void AGrass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void AGrass::OnObjectBeginPlay(AActor* Object)
{
    Super::OnObjectBeginPlay(Object);
	if (Object != this)
	{
		return;
	}
	/*if (MeshArray.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("AGrass::OnObjectBeginPlay(): MeshArray.Num() == 0"));
		return;
	}
	UStaticMesh* Mesh = MeshArray[FMath::RandRange(0, MeshArray.Num() - 1)];
	this->MeshComponent->SetStaticMesh(Mesh);
	this->MeshComponent->SetMaterial(0, Mesh->GetMaterial(0));*/

}


void AGrass::OnObjectEndPlay(AActor* Object)
{
	Super::OnObjectEndPlay(Object);
	if (Object != this)
	{
		return;
	}

}
