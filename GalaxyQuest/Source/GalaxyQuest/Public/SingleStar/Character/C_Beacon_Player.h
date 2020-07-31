// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_Beacon_Player.generated.h"

class UTextBlock;
class UImage;
class UButton;
class UScrollBox;

UCLASS()
class GALAXYQUEST_API UC_Beacon_Player : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

	UFUNCTION()
		void OpenShop();
	UFUNCTION()
		void CloseShop();

public:
	bool bIsShopShowing;

public:
	UPROPERTY()
		UTextBlock* Beacon_Name;
	UPROPERTY()
		UTextBlock* Beacon_Intro;
	UPROPERTY()
		UTextBlock* Open_TEXT;
	UPROPERTY()
		UTextBlock* Close_Text;
	UPROPERTY()
		UTextBlock* Money_Text;
	UPROPERTY()
		UTextBlock* TotalMoney_Text;
	UPROPERTY()
		UButton*	Close_Btn;
	UPROPERTY()
		UButton*	Open_Btn;
	UPROPERTY()
		UImage*		Beacon_Pic;
	UPROPERTY()
		UImage*		BG_Up;
	UPROPERTY()
		UImage*		BG_Down;
	UPROPERTY()
		UScrollBox* Roll_Up;
	UPROPERTY()
		UScrollBox* Roll_Down;
	UPROPERTY()
		UButton*	ClosePage_Btn;
	UPROPERTY()
		UTextBlock* ClosePage_Text;
};
