// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
{
	TotalScore = 0;
	CurrentLevelIndex = 0;
}

int32 UMyGameInstance::GetToScore() const
{
	return TotalScore;
}

void UMyGameInstance::AddToScore(int32 Amount)
{
	TotalScore += Amount;
	UE_LOG(LogTemp, Warning, TEXT("Total Score Updated: %d"), TotalScore);
}

int32 UMyGameInstance::GetCurrentLevelIndex(int32 Amount) const
{
	return CurrentLevelIndex;
}
