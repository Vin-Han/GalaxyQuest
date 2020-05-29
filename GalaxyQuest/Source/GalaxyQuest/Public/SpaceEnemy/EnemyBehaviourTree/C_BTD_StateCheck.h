// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "../Public/SpaceEnemy/C_SpaceEnemy_State.h"
#include "C_BTD_StateCheck.generated.h"

/**
 * 
 */
UCLASS()
class GALAXYQUEST_API UC_BTD_StateCheck : public UBTDecorator
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnyWhere, Category = "CheckState")
		EnemyState TargetState;

public:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;
};
