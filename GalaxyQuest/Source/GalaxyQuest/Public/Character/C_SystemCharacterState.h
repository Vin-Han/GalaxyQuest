// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "../Public/Bag/C_BulletItemBase.h"
#include "../Public/Bag/C_ShieldItemBase.h"
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

public:
	TArray<FBulletBagItem> BulletList;
	TArray<FSheildBagItem> ShieldList;

public:
	void AddItem(FBulletBagItem& newItem);
	void AddItem(FSheildBagItem& newItem);
};
