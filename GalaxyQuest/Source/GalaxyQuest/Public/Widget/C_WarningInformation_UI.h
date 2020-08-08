// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "C_WarningInformation_UI.generated.h"

class UTextBlock;

UCLASS()
class GALAXYQUEST_API UC_WarningInformation_UI : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;
	
	void SetWarningInformation(FString message, float occorTime = 3.0f, FColor messageColor = FColor::Red);
	
	UFUNCTION()
		void RemoveInformation();
	
public:
	UPROPERTY()
		UTextBlock* Infor_Text;

	FTimerHandle TH_Information;
};
