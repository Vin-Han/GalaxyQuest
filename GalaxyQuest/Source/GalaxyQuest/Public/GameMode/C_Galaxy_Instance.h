// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "C_Galaxy_Instance.generated.h"

class AC_Shield_Base;
struct FBulletBagItem;
struct FSheildBagItem;
struct FSourceBase;

UCLASS()
class GALAXYQUEST_API UC_Galaxy_Instance : public UGameInstance
{
	GENERATED_BODY()
public:
	float PlayerCurrentHp;
	float CurrentShield;
	TSubclassOf<AC_Shield_Base> CurrentEqipedShield;
	float Money;
	FString parentStarPath;
public:
	TArray<FBulletBagItem> BulletList;
	TArray<FSheildBagItem> ShieldList;
	TArray<FSourceBase> SourceList;

protected:
	virtual void OnStart() override;

	UPROPERTY()
		class UC_WarningInformation_UI* Infor_Widget;
public:
	void SendMessageToPlayer(FString message, float occorTime = 3.0f, FColor messageColor = FColor::Red);
};
