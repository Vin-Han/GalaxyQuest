// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
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

public:
	TArray<struct FBagItemBase> BagList;
};