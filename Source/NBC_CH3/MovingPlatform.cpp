// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	// 초기 위치 세팅(블루프린트에서 설정) == 초기위치에서 Dist값 계산 후 MaxRange를 넘어가면 방향 전환
	StartLocation = GetActorLocation();
	// 초기 이동 방향 세팅 == 엑터의 정면
	MoveDirection = GetActorForwardVector();
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MovePlatform(DeltaTime);
	
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	// 현재 위치 & 움직일 위치 선정
	FVector CurrentLocation = GetActorLocation();
	FVector NewLocation = CurrentLocation + (MoveDirection * MoveSpeed * DeltaTime);
	// Platform 이동
	SetActorLocation(NewLocation);
	// 이동 거리 계산
	float Dist = FVector::Dist(StartLocation, NewLocation);
	// Actor의 정면 방향으로 진행 중 최대 거리를 넘기면 방향 반대로 전환
	if (bMovingForward && Dist >= MaxRange)
	{
		MoveDirection = -MoveDirection;
		bMovingForward = false;
	}
	// 방향을 반대로 전환해 초기 위치에 근접하게 된다면 다시 방향 전환
	else if (bMovingForward == false && Dist <= 1.0f )
	{
		MoveDirection = -MoveDirection;
		bMovingForward = true;
	}
	
	if (IsValid(GEngine))
	{
		FString DebugMsg = FString::Printf(TEXT("Distance: %f / Dir: %s"), Dist, *MoveDirection.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, DebugMsg);
	}
}

