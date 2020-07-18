// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Public/Bag/C_BulletItemBase.h"
#include "../Public/Bag/C_ShieldItemBase.h"
#include "C_ShopPage.generated.h"

class UButton;
class UTextBlock;
class UImage;
class USlider;

UCLASS()
class GALAXYQUEST_API UC_ShopPage : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;

	UFUNCTION()
		void UpdateCurCount(float value);

	void UpdateTotalCount(int newCount);

public:
	UPROPERTY()
		UButton*		Button_BuyBtn;
	UPROPERTY()
		UImage*			Image_Item;
	UPROPERTY()
		UTextBlock*		Text_Name;
	UPROPERTY()
		UTextBlock*		Text_Intro;
	UPROPERTY()
		UTextBlock*		Text_CurCount;
	UPROPERTY()
		UTextBlock*		Text_TotalCount;
	UPROPERTY()
		USlider*		Slider_Buy;

public:
	int TotalCount;
	int CurCount;
	FBulletBagItem* BulletInfor;
	FSheildBagItem* ShieldInfor;
};
