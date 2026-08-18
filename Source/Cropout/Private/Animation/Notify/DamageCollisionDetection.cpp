// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/DamageCollisionDetection.h"
#include "NPC/NPC.h"

void UDamageCollisionDetection::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	ANPC* NPC = Cast<ANPC>(MeshComp->GetOwner());
	if(NPC == nullptr)
	{
        UE_LOG(LogTemp,Warning,TEXT("UDamageCollisionDetection::Notify(): NPC == nullptr"));
        return;
	}
	NPC->Attack();








}