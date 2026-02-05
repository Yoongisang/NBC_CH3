// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/MyGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Spawning/SpawnVolume.h"
#include "Item/CoinItem.h"
#include "Core/MyGameInstance.h"
#include "Player/MyPlayerController.h"
#include "Player/MyCharacter.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"

AMyGameState::AMyGameState()
{
	Score = 0;
	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;
	LevelDuration = 10.0f;
	CurrentLevelIndex = 0;
	MaxLevels = 3;
	CurrentWaveIndex = 1;
	MaxWaves = 3;
	ItemToSpawn = 40;
}

void AMyGameState::BeginPlay()
{
	Super::BeginPlay();
	// 시작 과 동시에 HUD 업데이트
	UpdateHUD();
	// Level시작 -> 아이템 스폰 및 GameInstance에 저장된 LevelInexd 받아오기
	StartLevel();
	// 이후로 0.1초마다 업데이트 반복
	GetWorldTimerManager().SetTimer(
		HUDUpdateTimerHandle,
		this,
		&AMyGameState::UpdateHUD,
		0.1f,
		true
	);
}

int32 AMyGameState::GetScore() const
{
	return Score;
}

void AMyGameState::AddScore(int32 Amount)
{
	// MyGameState에 누적 저장
	Score += Amount;
}

void AMyGameState::OnGameEnd()
{
	// 타이머 해제
	GetWorldTimerManager().ClearTimer(LevelTimerHandle);
	// 게임 종료(캐릭터 사망 및 Level전부 클리어) 시 메뉴 화면 띄우기
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (AMyPlayerController* PC = Cast<AMyPlayerController>(PlayerController))
		{
			PC->ShowMainMenu(true);
		}
	}
}

void AMyGameState::StartLevel()
{
	// HUD 갱신
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (AMyPlayerController* PC = Cast<AMyPlayerController>(PlayerController))
		{
			PC->ShowGameHUD();
		}
	}
	// GameInstance에 저장된 LevelIndex 받아오기(Level변경 시 GameState는 초기화 되기 때문에)
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GameInstance);
		if (MyGameInstance)
		{
			CurrentLevelIndex = MyGameInstance->GetCurrentLevelIndex();
			// 첫 웨이브때만 점수 동기화 == 이전 레벨의 최종 점수 불러오기
			if (CurrentWaveIndex == 1)
			{
				Score = MyGameInstance->GetToScore();
			}
			
		}
	}

	// 레벨 시작 시, 코인 개수 초기화 웨이브마다 누적으로 생성이라면 초기화 X
	//SpawnedCoinCount = 0;
	//CollectedCoinCount = 0;

	// 현재 맵에 배치된 모든 SpawnVolume을 찾아 정해진 수량 만큼 아이템 스폰
	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);

	for (int32 i = 0; i < ItemToSpawn; i++)
	{
		if (FoundVolumes.Num() > 0)
		{
			ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(FoundVolumes[0]);
			if (SpawnVolume)
			{
				AActor* SpawnedActor = SpawnVolume->SpawnRandomItem();
				// 만약 스폰된 액터가 코인 타입이라면 SpawnedCoinCount 증가
				if (SpawnedActor && SpawnedActor->IsA(ACoinItem::StaticClass()))
				{
					SpawnedCoinCount++;
				}
			}
		}
	}

	// 10초 후에 OnLevelTimeUp()가 호출되도록 타이머 설정
	GetWorldTimerManager().SetTimer(
		LevelTimerHandle,
		this,
		&AMyGameState::OnLevelTimeUp,
		LevelDuration,
		false
	);

	UpdateHUD();

	UE_LOG(LogTemp, Warning, TEXT("Level %d Start!, Spawned %d coin"),
		CurrentLevelIndex + 1,
		SpawnedCoinCount);
}

void AMyGameState::OnLevelTimeUp()
{
	// 시간이 다 되면 웨이브를 종료
	EndWave();
}

void AMyGameState::OnCoinCollected()
{
	// 모은 Coint 갯수 증가
	CollectedCoinCount++;

	UE_LOG(LogTemp, Warning, TEXT("Coin Collected: %d / %d"),
		CollectedCoinCount,
		SpawnedCoinCount);

		// 현재 레벨에서 스폰된 코인을 전부 주웠다면 즉시 웨이브 종료
		if (SpawnedCoinCount > 0 && CollectedCoinCount >= SpawnedCoinCount)
		{
			EndWave();
		}
}

void AMyGameState::EndWave()
{
	// 타이머 해제
	GetWorldTimerManager().ClearTimer(LevelTimerHandle);
	// 정해진 웨이브 횟수만큼은 Level을 넘어가지 않고 반복(라운드 시간과 아이템 스폰 수를 늘려서 난이도 조절)
	if (CurrentWaveIndex < MaxWaves)
	{
		CurrentWaveIndex++;
		LevelDuration += 5;
		ItemToSpawn += 5;
		// 바로 지금 상태에서 다음 웨이브 진행
		StartLevel();

		return;
	}
	// 모든 웨이브가 끝나면 다음 Level로
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GameInstance);
		if (MyGameInstance)
		{
			
			CurrentLevelIndex++;
			// GameState에 누적된 Score와 LevelIndex를 GameInstance에 저장
			MyGameInstance->SetCurrentLevelIndex(CurrentLevelIndex);
			MyGameInstance->SetToScore(Score);

			// 남은 LevelIndex가 있으면 다음 Level오픈 아니면 GameEnd
			if (LevelMapNames.IsValidIndex(CurrentLevelIndex))
			{
				UGameplayStatics::OpenLevel(GetWorld(), LevelMapNames[CurrentLevelIndex]);
			}
			else
			{
				OnGameEnd();
			}
		}
	}
}

void AMyGameState::UpdateHUD()
{
	// HUD 위젯의 시간, 점수, 현재 레벨, 현재 웨이브, 캐릭터 체력을 받아와서 SetText방식으로 업데이트
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (AMyPlayerController* PC = Cast<AMyPlayerController>(PlayerController))
		{
			if (UUserWidget* HUDWidget = PC->GetHUDWidget())
			{
				if (UTextBlock* TimeText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Time"))))
				{
					float RemainingTime = GetWorldTimerManager().GetTimerRemaining(LevelTimerHandle);
					TimeText->SetText(FText::FromString(FString::Printf(TEXT("Time: %.1f"), RemainingTime)));
				}

				if (UTextBlock* ScoreText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Score"))))
				{
					if (UGameInstance* GameInstance = GetGameInstance())
					{
						UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GameInstance);
						if (MyGameInstance)
						{
							ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), Score)));
						}
					}
				}

				if (UTextBlock* LevelIndexText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Level"))))
				{
					LevelIndexText->SetText(FText::FromString(FString::Printf(TEXT("Level: %d | Wave: %d"), CurrentLevelIndex + 1, CurrentWaveIndex)));
				}

				if (UTextBlock* HPText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Health"))))
				{
					if (AMyCharacter* MyCharacter = Cast<AMyCharacter>(PC->GetPawn()))
						HPText->SetText(FText::FromString(FString::Printf(TEXT("HP : %d"), MyCharacter->GetHealth())));
				}
			}
		}
	}

}
