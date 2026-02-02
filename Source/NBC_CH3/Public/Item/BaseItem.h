// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemInterface.h"
#include "BaseItem.generated.h"

UCLASS()
class NBC_CH3_API ABaseItem : public AActor, public IItemInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseItem();
protected:
	// 아이템 오버렙 함수 오버라이드
	virtual void OnItemOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) override;
	// 아이템 오버렙 해제 함수 오버라이드
	virtual void OnItemEndOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex) override;
	// 아이템 활성화 함수 오버라이드
	virtual void ActivateItem(AActor* Activator) override;
	virtual FName GetItemType() const override;

	void DestroyItem();

	// 멤버 변수
	// 아이템 타입
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FName ItemType;
	// 루트 컴포넌트 (씬)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	TObjectPtr<USceneComponent> Scene;
	// 충돌 컴포넌트 (플레이어 진입 범위 감지용)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	TObjectPtr<class USphereComponent> Collision;
	// 아이템 시각 표현용 스태틱 메시
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	TObjectPtr<UStaticMeshComponent> StaticMesh;
};
