// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatingPlatform.h"

// Sets default values
ARotatingPlatform::ARotatingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ARotatingPlatform::BeginPlay()
{
	Super::BeginPlay();
	// 초기 위치 세팅(블루프린트에서 설정)
	SetActorLocation(StartLocation);
	// 초기 Acotr 각도 세팅
	SetActorRotation(StartRotation);

	// FTimerHandle을 활용한 코드
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,
		this,
		&ARotatingPlatform::RotatePlatform,
		0.016f,
		true
	);
}

// Called every frame
void ARotatingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARotatingPlatform::RotatePlatform()
{
	// Platform 이동
	AddActorLocalRotation(RotateSpeed * 0.016f);
}

