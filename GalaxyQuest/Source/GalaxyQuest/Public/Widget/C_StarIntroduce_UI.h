// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_StarIntroduce_UI.generated.h"

class UButton;
class UTextBlock;
class UImage;

UCLASS()
class GALAXYQUEST_API UC_StarIntroduce_UI : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(Meta = (BindWidget))
		UButton* Button_Close;
	UPROPERTY(Meta = (BindWidget))
		UButton* Button_Explore;
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* TextBlock_Name;
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* TextBlock_Intro;
	UPROPERTY(Meta = (BindWidget))
		UImage* Image_Pic;
};
