// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class NBC_CH3_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UMyGameInstance();
	// 게임 전체 누적 점수 및 현재 레벨 인덱스 게터 세터
	UFUNCTION(BlueprintCallable, Category = "GameData")
	int32 GetToScore() const;

	UFUNCTION(BlueprintCallable, Category = "GameData")
	void SetToScore(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "GameData")
	void AddToScore(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "GameData")
	int32 GetCurrentLevelIndex() const;

	UFUNCTION(BlueprintCallable, Category = "GameData")
	void SetCurrentLevelIndex(int32 Amount);
private:
	// 게임 전체 누적 점수
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData", meta = (AllowPrivateAccess = "true"))
	int32 TotalScore;
	// 현재 레벨 인덱스 (GameState에서는 현재 Wave관리 현재 Level인덱스는 GameInstance에서)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData", meta = (AllowPrivateAccess = "true"))
	int32 CurrentLevelIndex;
};
