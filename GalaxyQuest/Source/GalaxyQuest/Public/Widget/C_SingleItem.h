// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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
		UImage*		Item_Pic;
};
