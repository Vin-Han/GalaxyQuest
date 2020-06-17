// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Public/Bag/C_BagItemBase.h"
#include "../Public/Projectile/C_Bullet_Base.h"
#include "C_BulletItemBase.generated.h"

USTRUCT(BlueprintType)
struct FBulletBagItem : public FBagItemBase
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnyWhere)
        int TotalAccout;

    UPROPERTY(EditAnyWhere)
        int CurrentAccout;

    UPROPERTY(EditAnyWhere)
        float CurrentLoadingTime;

    UPROPERTY(EditAnyWhere)
        TSubclassOf<AC_Bullet_Base> BulletClass;

};
