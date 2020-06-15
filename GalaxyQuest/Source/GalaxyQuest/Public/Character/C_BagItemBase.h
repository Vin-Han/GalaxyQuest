// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Public/Projectile/C_Bullet_Base.h"
#include "C_BagItemBase.generated.h"

USTRUCT(BlueprintType)
struct FBulletItem
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
