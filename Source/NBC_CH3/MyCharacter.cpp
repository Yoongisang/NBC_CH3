// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"


// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	// 캡슐(루트 컴포넌트)
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	RootComponent = CapsuleComp;
	CapsuleComp->SetSimulatePhysics(false);
	// 메시
	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
	MeshComp->SetSimulatePhysics(false);
	// 스프링 암
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	// 카메라
	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp);
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	// MappingContext 세팅
	if (APlayerController* PC = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// 바인드
	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);
		EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);
	}
}

void AMyCharacter::Move(const FInputActionValue& Value)
{
	// 키보드 입력값 X, Y 2D 벡터값으로 저장
	const FVector2D MoveInput = Value.Get<FVector2D>();
	// Tick밖에서 DeltaTime을 쓰는 방식
	const float DeltaTime = GetWorld()->GetDeltaSeconds();
	// 로그 출력
	if (IsValid(GEngine))
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, FString::Printf(TEXT("X: %f, Y: %f"), MoveInput.X, MoveInput.Y));
	}
	// Move 구현
	const FVector Movement = FVector(MoveInput.X, MoveInput.Y, 0.f) * MoveSpeed * DeltaTime;
	AddActorLocalOffset(Movement);
}

void AMyCharacter::Look(const FInputActionValue& Value)
{
	// 마우스 입력값 X, Y 2D 벡터값으로 저장
	const FVector2D MouseInput = Value.Get<FVector2D>();
	// Tick밖에서 DeltaTime을 쓰는 방식
	const float DeltaTime = GetWorld()->GetDeltaSeconds();

	// Look 구현
	// YawRotation 적용
	const FRotator YawRotation = FRotator(0.f, MouseInput.X * LookSensitivity * DeltaTime, 0.f);
	AddActorLocalRotation(YawRotation);
	//PitchRotation 적용 Pawn은 그대로 SpringArmComp의 Pitch값만 회전
	FRotator ArmRotation = SpringArmComp->GetRelativeRotation();
	ArmRotation.Pitch = FMath::Clamp(ArmRotation.Pitch - MouseInput.Y * LookSensitivity * DeltaTime, -80.f, 80.f);
	SpringArmComp->SetRelativeRotation(ArmRotation);

	// 로그 출력
	if (IsValid(GEngine))
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, FString::Printf(TEXT("X: %f, Y: %f"), MouseInput.X, MouseInput.Y));
	}
}

