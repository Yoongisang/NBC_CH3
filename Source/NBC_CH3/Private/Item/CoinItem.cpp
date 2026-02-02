// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/CoinItem.h"

ACoinItem::ACoinItem()
{
    // 점수 기본값을 0 아이템 타입 기본
    PointValue = 0;
    ItemType = "DefaultCoin";
}

void ACoinItem::ActivateItem(AActor* Activator)
{
    // 플레이어 태그 확인(플레이어 블루프린트에서 태그 설정)
    if (Activator && Activator->ActorHasTag("Player"))
    {
        // 점수 획득 디버그 메시지
        GEngine->AddOnScreenDebugMessage(
            -1, 2.0f, 
            FColor::Green, 
            FString::Printf(TEXT("Player gained %d points!"), PointValue));

        // 부모 클래스 (BaseItem)에 정의된 아이템 파괴 함수 호출
        DestroyItem();
    }
}
