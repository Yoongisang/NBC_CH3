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
	PrimaryActorTick.bCanEverTick = true;
	
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

	// Physics false 나중에 한번 생성자에서 디폴트 설정만 해야할지 아니면 게임시작 후 체크하고 false로 고정해줘야 하는지 질문 필요
	if (CapsuleComp->IsSimulatingPhysics())
	{
		CapsuleComp->SetSimulatePhysics(false);
	}

	if (MeshComp->IsSimulatingPhysics())
	{
		MeshComp->SetSimulatePhysics(false);
	}
	// MappingContext 세팅
	if (APlayerController* PC = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	FVector2D MoveInput = Value.Get<FVector2D>();
	// 로그 출력
	if (IsValid(GEngine))
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, FString::Printf(TEXT("X: %f, Y: %f"), MoveInput.X, MoveInput.Y));
	}
	// Move 구현
	FVector Movement = FVector(MoveInput.X, MoveInput.Y, 0.f) * MoveSpeed * GetWorld()->GetDeltaSeconds();;
	AddActorLocalOffset(Movement);
}

void AMyCharacter::Look(const FInputActionValue& Value)
{
	FVector2D MouseInput = Value.Get<FVector2D>();
	// Tick밖에서 DeltaTime을 쓰는 방식
	float Deltatime = GetWorld()->GetDeltaSeconds();

	// Look 구현
	// YawRotation
	FRotator YawRotation = FRotator(0.f, MouseInput.X * LookSensitivity * Deltatime, 0.f);	
	AddActorLocalRotation(YawRotation);
	//PitchRotation
	FRotator ArmRotation = SpringArmComp->GetRelativeRotation();
	ArmRotation.Pitch = FMath::Clamp(ArmRotation.Pitch - MouseInput.Y * LookSensitivity * Deltatime, -80.f, 80.f);
	SpringArmComp->SetRelativeRotation(ArmRotation);

	// 로그 출력
	if (IsValid(GEngine))
	{
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Red, FString::Printf(TEXT("X: %f, Y: %f"), MouseInput.X, MouseInput.Y));
	}
	
	
}

