// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_StarLocation_UI.generated.h"

/**
 * 
 */
UCLASS()
class GALAXYQUEST_API UC_StarLocation_UI : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;

public:
	UPROPERTY()
		class UTextBlock* Text_StarLocation;
	UPROPERTY()
		UTextBlock* Text_StarDistance;
};
