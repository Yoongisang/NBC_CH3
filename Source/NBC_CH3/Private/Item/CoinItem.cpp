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
}
