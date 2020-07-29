// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_Beacon_Item.generated.h"

class UButton;
class UTextBlock;
class USlider;
struct FSourceBase;

UCLASS()
class GALAXYQUEST_API UC_Beacon_Item : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

public:
	UPROPERTY()
		UButton*	Btn_Buy;
	UPROPERTY()
		UTextBlock* Text_Buy;
	UPROPERTY()
		UTextBlock* Text_Name;
	UPROPERTY()
		UTextBlock* Text_Price;
	UPROPERTY()
		UTextBlock* Text_Count;
	UPROPERTY()
		UTextBlock* Text_BuyCount;
	UPROPERTY()
		UTextBlock* Text_BuyPrice;
	UPROPERTY()
		USlider*	Bar_Buy;
public:
	FSourceBase* targetItem;

public:
	UFUNCTION()
		void UpdateSlider(float value);
};
