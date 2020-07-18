// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Public/Bag/C_BagItemBase.h"
#include "../Public/Shield/C_Shield_Base.h"
#include "C_ShieldItemBase.generated.h"

USTRUCT(BlueprintType)
struct FSheildBagItem : public FBagItemBase
{
    GENERATED_USTRUCT_BODY()

    bool bIfShowOnShop;

    UPROPERTY(EditAnyWhere)
        TSubclassOf<AC_Shield_Base> ShieldClass;

};