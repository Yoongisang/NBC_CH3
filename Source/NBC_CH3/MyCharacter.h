// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyCharacter.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class NBC_CH3_API AMyCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
#pragma region Component
	// 캡슐 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	TObjectPtr<UCapsuleComponent> CapsuleComp;
	// 메시 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	TObjectPtr<USkeletalMeshComponent> MeshComp;
	// 스프링 암 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	TObjectPtr<USpringArmComponent> SpringArmComp;
	// 카메라 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	TObjectPtr<UCameraComponent> CameraComp;
#pragma endregion

#pragma region Input
	// InputMappingContext
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	// Move
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;
	// Look
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> LookAction;
	// MoveSpeed
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	float MoveSpeed;
	// LookSensitivity
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	float LookSensitivity;
#pragma endregion


public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
#pragma region Action
	// Input Action
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
#pragma endregion
};
