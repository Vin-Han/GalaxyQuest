// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "C_Source_Form.generated.h"


USTRUCT(BlueprintType)
struct FSourceData : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

public:
    UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "SourceForm")
        int ID;
    UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "SourceForm")
        FString Name;
    UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "SourceForm")
        FString Describe;
    UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "SourceForm")
        int MinPrice;
    UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "SourceForm")
        int MaxPrice;
    UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "SourceForm")
        int MinCount;
    UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "SourceForm")
        int MaxCount;
    UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "SourceForm")
        float OccurPercent;
};
