// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/BaseItem.h"
#include "MineItem.generated.h"

/**
 * 
 */
UCLASS()
class NBC_CH3_API AMineItem : public ABaseItem
{
	GENERATED_BODY()
	
public:
    AMineItem();

protected:
    // ActivateItem 오버라이드
    virtual void ActivateItem(AActor* Activator) override;
    // 폭발 구현 부분
    void Explode();

private:
    // 멤버 변수
    // 지뢰 발동 여부
    FTimerHandle ExplosionTimerHandle;
    // 오버렙 범위 판정을위한 collision
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USphereComponent> ExplosionCollision;
    // 폭발까지 걸리는 시간 (5초)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mine", meta = (AllowPrivateAccess = "true"))
    float ExplosionDelay;
    // 폭발 범위
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mine", meta = (AllowPrivateAccess = "true"))
    float ExplosionRadius;
    // 폭발 데미지
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mine", meta = (AllowPrivateAccess = "true"))
    int ExplosionDamage;

   
};
