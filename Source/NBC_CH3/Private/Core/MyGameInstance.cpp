// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
{
}

int32 UMyGameInstance::GetToScore() const
{
	return TotalScore;
}

void UMyGameInstance::AddToScore(int32 Amount)
{
}

int32 UMyGameInstance::GetCurrentLevelIndex(int32 Amount) const
{
	return CurrentLevelIndex;
}
