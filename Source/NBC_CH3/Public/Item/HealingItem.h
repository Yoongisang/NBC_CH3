// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/BaseItem.h"
#include "HealingItem.generated.h"

/**
 * 
 */
UCLASS()
class NBC_CH3_API AHealingItem : public ABaseItem
{
	GENERATED_BODY()

public:
    AHealingItem();

protected:
    // ActivateItem 함수를 오버라이드
    virtual void ActivateItem(AActor* Activator) override;

private:
    // 회복량
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Healing", meta = (AllowPrivateAccess = "true"))
    int32 HealAmount;
};
