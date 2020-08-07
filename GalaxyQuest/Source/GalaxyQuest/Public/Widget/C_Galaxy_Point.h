// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_Galaxy_Point.generated.h"

class UButton;

UCLASS()
class GALAXYQUEST_API UC_Galaxy_Point : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

public:
	UFUNCTION()
		void SetGameModeInfor();

public:
	UPROPERTY()
		UButton* Btn_Point;
	
	UPROPERTY(EditAnyWhere,Category = "System")
		FString SystemName;
	UPROPERTY(EditAnyWhere, Category = "System")
		FString SystemPath;
	UPROPERTY(EditAnyWhere, Category = "System")
		FString SystemIntro;
	
};
