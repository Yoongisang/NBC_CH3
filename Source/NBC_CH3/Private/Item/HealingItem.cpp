// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/HealingItem.h"
#include "Player/MyCharacter.h"

AHealingItem::AHealingItem()
{
	// 회복량 및 ItemType 설정
	HealAmount = 20.0f;
	ItemType = "Healing";
}

void AHealingItem::ActivateItem(AActor* Activator)
{
	if (Activator && Activator->ActorHasTag("Player"))
	{
		if (AMyCharacter* PlayerCharacter = Cast<AMyCharacter>(Activator))
		{
			// 캐릭터의 체력을 회복
			PlayerCharacter->AddHealth(HealAmount);
		}

		DestroyItem();
	}
}
