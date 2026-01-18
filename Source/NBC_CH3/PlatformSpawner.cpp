// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformSpawner.h"
#include "MovingPlatform.h"
#include "RotatingPlatform.h"

void APlatformSpawner::SpawnMovingPlatforms()
{
	// GetWorld()의 SpawnActor 사용을 위한 선언 및 nullptr값 검사
	UWorld* World = GetWorld();
	if (World == nullptr)
	{
		return;
	}
	// 블루프린트에서 설정한 갯수 만큼 생성
	for (int32 i = 0; i < MovingPlatformCount; i++)
	{
		// 블루 프린트에서 MovingPlatformClass 설정한 값이 있다면 생성
		if (IsValid(MovingPlatformClass))
		{
			// 랜덤 위치 각도는 일관적으로(일자 맵에서 진로방해하는 제각각 움직이는 랜덤 장애물)
			FVector Location = GetRandomLocation();
			FRotator Rotation = FRotator::ZeroRotator;
			// 월드에 액터 스폰
			AMovingPlatform* Platform = World->SpawnActor<AMovingPlatform>(
				MovingPlatformClass,
				Location,
				Rotation
			);
			// Platform이 존재한다면 속도와 최대 이동 범위 랜덤
			if (IsValid(Platform))
			{
				Platform->SetMoveSpeed(FMath::RandRange(300.f, 500.f));
				Platform->SetMaxRange(FMath::RandRange(1000.f, 5000.f));
			}
		}
	}
}

void APlatformSpawner::SpawnRotatingPlatforms()
{
	// GetWorld()의 SpawnActor 사용을 위한 선언 및 nullptr값 검사
	UWorld* World = GetWorld();
	if (World == nullptr)
	{
		return;
	}
	// 블루프린트에서 설정한 갯수 만큼 생성
	for (int32 i = 0; i < RotatingPlatformCount; i++)
	{
		// 블루 프린트에서 RotatingPlatformClass 설정한 값이 있다면 생성
		if (IsValid(RotatingPlatformClass))
		{
			// 위치와 각도 둘다 랜덤 각도의 경우(Pitch, Yaw)
			FVector Location = GetRandomLocation();
			FRotator Rotation = GetRandomRotation();
			// 월드에 액터 스폰
			ARotatingPlatform* Platform = World->SpawnActor<ARotatingPlatform>(
				RotatingPlatformClass,
				Location,
				Rotation
			);
	
			if (IsValid(Platform))
			{
				// 회전 속도 랜덤
				Platform->SetRotateSpeed(FRotator(0.f, FMath::RandRange(30.f, 50.f), 0.f));
			}
		}
	}
}

// Sets default values
APlatformSpawner::APlatformSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void APlatformSpawner::BeginPlay()
{
	Super::BeginPlay();
	// Play후 랜덤 스폰
	SpawnMovingPlatforms();
	SpawnRotatingPlatforms();
}

FVector APlatformSpawner::GetRandomLocation()
{
	// 위치값 랜덤 생성
	return FVector(
		FMath::RandRange(SpawnAreaMin.X, SpawnAreaMax.X),
		FMath::RandRange(SpawnAreaMin.Y, SpawnAreaMax.Y),
		FMath::RandRange(SpawnAreaMin.Z, SpawnAreaMax.Z)
	);
}

FRotator APlatformSpawner::GetRandomRotation()
{
	// Pitch(y), Yaw(z) 축 기준 각도값 랜덤 생성
	return FRotator(FMath::RandRange(10.f, 30.f), FMath::RandRange(0.f, 360.f), 0.f);
}


