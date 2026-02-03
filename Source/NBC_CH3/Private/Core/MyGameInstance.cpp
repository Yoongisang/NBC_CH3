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

void UMyGameInstance::SetToScore(int32 Amount)
{
	TotalScore = Amount;
}

void UMyGameInstance::AddToScore(int32 Amount)
{
	TotalScore += Amount;
	UE_LOG(LogTemp, Warning, TEXT("Total Score Updated: %d"), TotalScore);
}

void UMyGameInstance::SetCurrentLevelIndex(int32 Amount)
{
	CurrentLevelIndex = Amount;
	UE_LOG(LogTemp, Warning, TEXT("CurrentLevelIndex Updated: %d"), CurrentLevelIndex + 1);
}

int32 UMyGameInstance::GetCurrentLevelIndex() const
{
	return CurrentLevelIndex;
}
