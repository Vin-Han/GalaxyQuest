// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "C_StartGameModeBase.generated.h"

class UC_Start_UI;

UCLASS()
class GALAXYQUEST_API AC_StartGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void StartPlay() override;

	UFUNCTION()
		void QuitCurGame();
	UFUNCTION()
		void OpenTargetLevel();

	void SetWidgetInfor(FString SystemPath, FString SystemName, FString SystemIntro);

public:
	UPROPERTY()
		UC_Start_UI* StartUI;

	FString targetSystemPath;

};
