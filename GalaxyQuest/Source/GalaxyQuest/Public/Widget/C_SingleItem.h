// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Public/Bag/C_BulletItemBase.h"
#include "../Public/Bag/C_ShieldItemBase.h"
#include "C_SingleItem.generated.h"

class UTextBlock;
class UButton;
class UImage;


UCLASS()
class GALAXYQUEST_API UC_SingleItem : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

	UFUNCTION()
		void BindControllerItem();
public:
	UPROPERTY()
		UTextBlock* Item_Name;
	UPROPERTY()
		UTextBlock* Item_Intro;
	UPROPERTY()
		UTextBlock* Item_BtnName;
	UPROPERTY()
		UButton*	Item_Btn;
	UPROPERTY()
		UButton*	Item_WholeBtn;
	UPROPERTY()
		UImage*		Item_Pic;

	FBulletBagItem* BulletInfor;
	FSheildBagItem* ShieldInfor;
	APlayerController* CurrentContoller;
};
