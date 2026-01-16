// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatingPlatform.h"

// Sets default values
ARotatingPlatform::ARotatingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARotatingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARotatingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RotatePlatform(DeltaTime);
}

void ARotatingPlatform::RotatePlatform(float DeltaTime)
{
	// 현재 각도 & 회전할 각도 설정
	FRotator CurrentRotation = GetActorRotation();
	FRotator NewRotation = CurrentRotation + (RotateSpeed * DeltaTime);
	// Platform 이동
	SetActorRotation(NewRotation);
}

