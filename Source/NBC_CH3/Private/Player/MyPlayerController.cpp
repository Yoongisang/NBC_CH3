// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MyPlayerController.h"
#include "Core/MyGameInstance.h"
#include "Core/MyGameState.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetSystemLibrary.h"

AMyPlayerController::AMyPlayerController()
	: InputMappingContext(nullptr),
	MoveAction(nullptr),
	JumpAction(nullptr),
	LookAction(nullptr),
	SprintAction(nullptr),
	HUDWidgetClass(nullptr),
	HUDWidgetInstance(nullptr),
	MainMenuWidgetClass(nullptr),
	MainMenuWidgetInstance(nullptr)
{
}

UUserWidget* AMyPlayerController::GetHUDWidget() const
{
	return HUDWidgetInstance;
}

void AMyPlayerController::ShowGameHUD()
{
	// HUD가 켜져 있다면 닫기
	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr;
	}

	// 이미 메뉴가 떠 있으면 제거
	if (MainMenuWidgetInstance)
	{
		MainMenuWidgetInstance->RemoveFromParent();
		MainMenuWidgetInstance = nullptr;
	}

	if (HUDWidgetClass)
	{
		HUDWidgetInstance = CreateWidget<UUserWidget>(this, HUDWidgetClass);
		if (HUDWidgetInstance)
		{
			HUDWidgetInstance->AddToViewport();

			bShowMouseCursor = false;
			SetInputMode(FInputModeGameOnly());

			AMyGameState* GameState = GetWorld() ? GetWorld()->GetGameState<AMyGameState>() : nullptr;
			if (GameState)
			{
				GameState->UpdateHUD();
			}
		}
	}
}

void AMyPlayerController::ShowMainMenu(bool bIsRestart)
{
	// HUD가 켜져 있다면 닫기
	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr;
	}

	// 이미 메뉴가 떠 있으면 제거
	if (MainMenuWidgetInstance)
	{
		MainMenuWidgetInstance->RemoveFromParent();
		MainMenuWidgetInstance = nullptr;
	}

	// 메뉴 UI 생성
	if (MainMenuWidgetClass)
	{
		MainMenuWidgetInstance = CreateWidget<UUserWidget>(this, MainMenuWidgetClass);
		if (MainMenuWidgetInstance)
		{
			MainMenuWidgetInstance->AddToViewport();
			bShowMouseCursor = true;
			SetInputMode(FInputModeUIOnly());
		}
		// 첫 번째 버튼 (Start/Restart) 재활용
		if (UTextBlock* ButtonText = Cast<UTextBlock>(MainMenuWidgetInstance->GetWidgetFromName(TEXT("StartButtonText"))))
		{
			if (bIsRestart)
			{
				ButtonText->SetText(FText::FromString(TEXT("Restart")));
			}
			else
			{
				ButtonText->SetText(FText::FromString(TEXT("Start")));
			}
		}
		// 2. 두 번째 버튼 (Exit/Main Menu) 텍스트 재활용
		if (UTextBlock* ExitText = Cast<UTextBlock>(MainMenuWidgetInstance->GetWidgetFromName(TEXT("ExitButtonText"))))
		{
			if (bIsRestart)
			{
				// 게임 오버 상황 -> "메인으로"
				ExitText->SetText(FText::FromString(TEXT("Main Menu")));
			}
			else
			{
				// 메인 메뉴 상황 -> "종료"
				ExitText->SetText(FText::FromString(TEXT("Exit")));
			}
		}
	}
}

void AMyPlayerController::StartGame()
{
	// 메뉴 창에서 Start 입력 -> GameInstance의 LevelIndex = 0 ToScore = 0 입력 
	if (UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(this)))
	{
		GameInstance->SetCurrentLevelIndex(0);
		GameInstance->SetToScore(0);
	}
	// 인덱스 0 Level오픈
	UGameplayStatics::OpenLevel(GetWorld(), FName("BasicLevel"));
}

void AMyPlayerController::RetryLevel()
{
	// 현재 Level 다시 시작
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()));
}

void AMyPlayerController::QuitGame()
{
	// 종료
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}

void AMyPlayerController::GoToMainMenu()
{
	// 첫 메인 메뉴로 돌아감
	UGameplayStatics::OpenLevel(this, FName("MenuLevel"));
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext)
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}

	// 게임 실행 시 메뉴 레벨에서 메뉴 UI 먼저 표시
	FString CurrentMapName = GetWorld()->GetMapName();
	if (CurrentMapName.Contains("MenuLevel"))
	{
		ShowMainMenu(false);
	}
}
