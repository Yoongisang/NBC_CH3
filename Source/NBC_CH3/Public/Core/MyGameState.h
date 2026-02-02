// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MyGameState.generated.h"

/**
 * 
 */
UCLASS()
class NBC_CH3_API AMyGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	AMyGameState();

	virtual void BeginPlay() override;

	// 게터 세터 함수(score)
	UFUNCTION(BlueprintPure, Category = "Score")
	int32 GetScore() const;
	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddScore(int32 Amount);
	// 게임이 완전히 끝났을 때 (모든 레벨 종료 || 사망) 실행되는 함수
	UFUNCTION(BlueprintCallable, Category = "Level")
	void OnGameEnd();

	// 레벨을 시작할 때, 아이템 스폰 및 타이머 설정
	void StartLevel();
	// 레벨 제한 시간이 만료되었을 때 호출
	void OnLevelTimeUp();
	// 코인을 주웠을 때 호출
	void OnCoinCollected();
	// 웨이브가 끝나면 호출
	void EndWave();
	// HUD 업데이트
	void UpdateHUD();
	// 매 레벨이 끝나기 전까지 시간이 흐르도록 관리하는 타이머
	FTimerHandle LevelTimerHandle;
	// HUD를 업데이트 하기위한 타이머
	FTimerHandle HUDUpdateTimerHandle;

	// 현재 점수
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Score", meta = (AllowPrivateAccess = "true"))
	int32 Score;
	// 현재 레벨에서 스폰된 코인 개수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin", meta = (AllowPrivateAccess = "true"))
	int32 SpawnedCoinCount;
	// 플레이어가 수집한 코인 개수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Coin", meta = (AllowPrivateAccess = "true"))
	int32 CollectedCoinCount;
	// 각 레벨이 유지되는 시간 (초 단위)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level", meta = (AllowPrivateAccess = "true"))
	float LevelDuration;
	// 현재 진행 중인 레벨 인덱스
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level", meta = (AllowPrivateAccess = "true"))
	int32 CurrentLevelIndex;
	// 전체 레벨의 개수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Level", meta = (AllowPrivateAccess = "true"))
	int32 MaxLevels;
	// 실제 레벨 맵 이름 배열. 여기 있는 인덱스를 차례대로 연동
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level", meta = (AllowPrivateAccess = "true"))
	TArray<FName> LevelMapNames;
	// 현재 진행 중인 웨이브 인덱스
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wave", meta = (AllowPrivateAccess = "true"))
	int32 CurrentWaveIndex;
	// 전체 웨이브의 개수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wave", meta = (AllowPrivateAccess = "true"))
	int32 MaxWaves;
	// 현재 진행 중인 웨이브의 아이템 스폰 갯수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wave", meta = (AllowPrivateAccess = "true"))
	int32 ItemToSpawn;



};
