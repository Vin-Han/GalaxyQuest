// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_SolarUserFace.generated.h"


UCLASS()
class GALAXYQUEST_API UC_SolarUserFace : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY()
		class UProgressBar* Bar_Speed;
	UPROPERTY()
		UProgressBar* Bar_Vertical;
	UPROPERTY()
		UProgressBar* Bar_Horizontal;

public:
	virtual bool Initialize() override;
};
