// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "../Public/Bag/C_BulletItemBase.h"
#include "../Public/Bag/C_ShieldItemBase.h"
#include "../Public/SingleStar/Beacon/C_Source_Item.h"
#include "C_SystemCharacterState.generated.h"

/**
 * 
 */
UCLASS()
class GALAXYQUEST_API AC_SystemCharacterState : public APlayerState
{
	GENERATED_BODY()
	
public:
	float PlayerCurrentHp;
	float CurrentShield;
	AC_Shield_Base* CurrentEqipedShield;
	float Money;

public:
	TArray<FBulletBagItem> BulletList;
	TArray<FSheildBagItem> ShieldList;
	TArray<FSourceBase> SourceList;
public:
	bool AddItem(FBulletBagItem* newItem);
	bool AddItem(FSheildBagItem* newItem);
	bool AddItem(FSourceBase* newItem);
	bool SubItem(FSourceBase* newItem);
public:
	bool LoadStateFromInstance();
	bool StoreStateToInstance(bool bIfStoreStarPath);
};
