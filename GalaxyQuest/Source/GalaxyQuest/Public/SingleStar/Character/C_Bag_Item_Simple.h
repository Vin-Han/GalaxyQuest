// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_Bag_Item_Simple.generated.h"

class UTextBlock;

UCLASS()
class GALAXYQUEST_API UC_Bag_Item_Simple : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;
public:
	UPROPERTY()
		UTextBlock* Item_Name;
	UPROPERTY()
		UTextBlock* Item_Count;
};
