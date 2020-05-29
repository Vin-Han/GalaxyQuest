// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "C_BTD_DistanceCheck.generated.h"

/**
 * 
 */
UCLASS()
class GALAXYQUEST_API UC_BTD_DistanceCheck : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;
};
