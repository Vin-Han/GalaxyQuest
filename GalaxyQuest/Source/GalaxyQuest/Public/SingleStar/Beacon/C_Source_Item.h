// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "../Form/C_Source_Form.h"
#include "C_Source_Item.generated.h"

USTRUCT(BlueprintType)
struct FSourceBase
{
    GENERATED_USTRUCT_BODY()

public:
    int totalCount;
    int singlePrice;
public:
    int curCount;
    int curPrice;
public:
    FSourceData* targetItem;
public:
    void UpdateState();
};
