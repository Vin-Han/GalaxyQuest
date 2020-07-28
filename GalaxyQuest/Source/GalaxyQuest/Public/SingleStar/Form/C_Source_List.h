// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "C_Source_List.generated.h"

struct FSourceData;

UCLASS()
class GALAXYQUEST_API UC_Source_List : public UObject
{
	GENERATED_BODY()
public:
	virtual bool Initialize();

	UFUNCTION()
		static UC_Source_List* GetList();

	void GetAllItem(TArray<FSourceData*>& outItems);

public:
	UPROPERTY()
		UDataTable* sourceData;
};
