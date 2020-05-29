// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/SpaceEnemy/EnemyBehaviourTree/C_BTD_StateCheck.h"
#include "../Public/SpaceEnemy/C_ShaceEnemyController.h"
#include "../Public/SpaceEnemy/C_SpaceEnemy.h"

bool UC_BTD_StateCheck::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const{
	AC_ShaceEnemyController* Controller = Cast<AC_ShaceEnemyController>(OwnerComp.GetAIOwner());
	if (Controller->EnemyShip->CurrentState == TargetState){
		return true;
	}
	return false;
}