// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/SpaceEnemy/EnemyBehaviourTree/C_BTD_PartolRotateConfirm.h"
#include "../Public/SpaceEnemy/C_ShaceEnemyController.h"

bool UC_BTD_PartolRotateConfirm::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const{
	AC_ShaceEnemyController* Controller = Cast<AC_ShaceEnemyController>(OwnerComp.GetAIOwner());
	if (Controller){
		return Controller->bCanReset;
	}
	return false;
}