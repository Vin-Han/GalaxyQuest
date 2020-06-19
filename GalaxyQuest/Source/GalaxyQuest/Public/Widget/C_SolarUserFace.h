// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_SolarUserFace.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class GALAXYQUEST_API UC_SolarUserFace : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY()
		class UProgressBar* Bar_SpeedUp;
	UPROPERTY()
		UProgressBar* Bar_Speed;
	UPROPERTY()
		UProgressBar* Bar_ExtraSpeed;
	UPROPERTY()
		UProgressBar* Bar_Horizontal;
	UPROPERTY()
		UProgressBar* Bar_Blood;
	UPROPERTY()
		UProgressBar* Bar_Shield;

#pragma region Bullet Property
	UPROPERTY()
		UImage* Image_WP_1;
	UPROPERTY()
		UImage* Image_WP_P1;
	UPROPERTY()
		UProgressBar* Bar_WP_1;
	UPROPERTY()
		UTextBlock* Text_WP_1;

	UPROPERTY()
		UImage* Image_WP_2;
	UPROPERTY()
		UImage* Image_WP_P2;
	UPROPERTY()
		UProgressBar* Bar_WP_2;
	UPROPERTY()
		UTextBlock* Text_WP_2;

	UPROPERTY()
		UImage* Image_WP_3;
	UPROPERTY()
		UImage* Image_WP_P3;
	UPROPERTY()
		UProgressBar* Bar_WP_3;
	UPROPERTY()
		UTextBlock* Text_WP_3;

	UPROPERTY()
		UImage* Image_WP_4;
	UPROPERTY()
		UImage* Image_WP_P4;
	UPROPERTY()
		UProgressBar* Bar_WP_4;
	UPROPERTY()
		UTextBlock* Text_WP_4;

	UPROPERTY()
		UImage* Image_WP_5;
	UPROPERTY()
		UImage* Image_WP_P5;
	UPROPERTY()
		UProgressBar* Bar_WP_5;
	UPROPERTY()
		UTextBlock* Text_WP_5;
#pragma endregion

public:
	TArray<UImage*> BulletOut;
	TArray<UImage*> BulletPic;
	TArray<UProgressBar*> BulletCD;
	TArray<UTextBlock*> BulletNum;
public:
	virtual bool Initialize() override;
};
