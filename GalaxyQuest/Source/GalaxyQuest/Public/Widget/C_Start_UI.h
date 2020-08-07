// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_Start_UI.generated.h"

class UButton;
class UTextBlock;
class UImage;
class UC_Galaxy_UI;

/**
 * 
 */
UCLASS()
class GALAXYQUEST_API UC_Start_UI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UPROPERTY()
		UButton*	Btn_Into;
	UPROPERTY()
		UButton*	Btn_Quit;
	UPROPERTY()
		UTextBlock* Text_Name;
	UPROPERTY()
		UTextBlock* Text_Intro;
	UPROPERTY()
		UImage*		Img_Galaxy;
	UPROPERTY()
		UC_Galaxy_UI* WG_Galaxy;
	
};
