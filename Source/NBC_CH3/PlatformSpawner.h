// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformSpawner.generated.h"

UCLASS()
class NBC_CH3_API APlatformSpawner : public AActor
{
	GENERATED_BODY()
	
protected:
	// 스폰 관련 변수(블루 프린트에서 설정)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Setting")
	TSubclassOf<AActor> MovingPlatformClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Setting")
	TSubclassOf<AActor> RotatingPlatformClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Setting")
	int32 MovingPlatformCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Setting")
	int32 RotatingPlatformCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Setting")
	FVector SpawnAreaMin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Setting")
	FVector SpawnAreaMax;
	// 스폰 함수
	void SpawnMovingPlatforms();
	void SpawnRotatingPlatforms();
public:	
	// Sets default values for this actor's properties
	APlatformSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	FVector GetRandomLocation();
	FRotator GetRandomRotation();
};
