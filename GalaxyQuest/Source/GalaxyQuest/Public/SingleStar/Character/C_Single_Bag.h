// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_Single_Bag.generated.h"


class UTextBlock;
class UButton;
class UImage;
class UScrollBox;

UCLASS()
class GALAXYQUEST_API UC_Single_Bag : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;
public:
	UPROPERTY()
		UScrollBox* List_Roll;
	UPROPERTY()
		UImage*		Star_Img;
	UPROPERTY()
		UTextBlock* Star_Name;
	UPROPERTY()
		UTextBlock* Star_Intro;
	UPROPERTY()
		UTextBlock* Star_Infor;
	UPROPERTY()
		UButton*	Btn_Close;
	UPROPERTY()
		UButton*	Btn_Quit;

};
