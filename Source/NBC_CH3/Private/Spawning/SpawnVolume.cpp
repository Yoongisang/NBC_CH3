// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawning/SpawnVolume.h"

// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

AActor* ASpawnVolume::SpawnRandomItem()
{
	return nullptr;
}

AActor* ASpawnVolume::SpawnItem(TSubclassOf<AActor> ItemClass)
{
	return nullptr;
}

FVector ASpawnVolume::GetRandomPointInVolume() const
{
	return FVector();
}

FItemSpawnRow* ASpawnVolume::GetRandomItem() const
{
	return nullptr;
}


