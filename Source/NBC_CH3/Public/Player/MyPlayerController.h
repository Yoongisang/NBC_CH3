// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class NBC_CH3_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
    AMyPlayerController();

    UFUNCTION(BlueprintPure, Category = "HUD")
    UUserWidget* GetHUDWidget() const;
    // HUD 표시
    UFUNCTION(BlueprintCallable, Category = "HUD")
    void ShowGameHUD();
    // 메인 메뉴 표시
    UFUNCTION(BlueprintCallable, Category = "Menu")
    void ShowMainMenu(bool bIsRestart);
    // 게임 시작
    UFUNCTION(BlueprintCallable, Category = "Menu")
    void StartGame();
    // 레벨 재시작
    UFUNCTION(BlueprintCallable, Category = "Menu")
    void RetryLevel();
    // 게임 종료
    UFUNCTION(BlueprintCallable, Category = "Menu")
    void QuitGame();
    // 메인 메뉴로
    UFUNCTION(BlueprintCallable, Category = "Menu")
    void GoToMainMenu();

    // InputAction
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    TObjectPtr<class UInputMappingContext> InputMappingContext;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    TObjectPtr<class UInputAction> MoveAction;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    TObjectPtr<class UInputAction> JumpAction;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    TObjectPtr<class UInputAction> LookAction;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    TObjectPtr<class UInputAction> SprintAction;

    // UMG 위젯 클래스를 에디터에서 할당받을 변수
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> HUDWidgetClass;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HUD")
    UUserWidget* HUDWidgetInstance;
    // 메뉴 UI
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu")
    TSubclassOf<UUserWidget> MainMenuWidgetClass;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Menu")
    UUserWidget* MainMenuWidgetInstance;

protected:
    virtual void BeginPlay() override;
};
