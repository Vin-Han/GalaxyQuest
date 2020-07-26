// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_Beacon_UI.generated.h"

class UTextBlock;

UCLASS()
class GALAXYQUEST_API UC_Beacon_UI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

public:
	UPROPERTY()
		UTextBlock* Text_Name;
	UPROPERTY()
		UTextBlock* Text_Information;
};
