// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_UserBag.generated.h"

class UTextBlock;
class UButton;
class UImage;
class UProgressBar;
class UScrollBox;

UCLASS()
class GALAXYQUEST_API UC_UserBag : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;
public:
	UPROPERTY()
		UScrollBox*		Left_Roll;
	UPROPERTY()
		UScrollBox*		Right_Roll;
	UPROPERTY()
		UButton*		Exit_Btn;
	UPROPERTY()
		UButton*		Left_Btn;
	UPROPERTY()
		UButton*		Right_Btn;
	UPROPERTY()
		UProgressBar*	HP_Bar;
	UPROPERTY()
		UProgressBar*	Shield_Bar;
	UPROPERTY()
		UTextBlock*		Intro_Text;
	UPROPERTY()
		UImage*			Load_Image;

};
