// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/SpaceEnemy/EnemyBehaviourTree/C_BTT_NormalAtk.h"
#include "../Public/SpaceEnemy/C_ShaceEnemyController.h"

EBTNodeResult::Type UC_BTT_NormalAtk::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) 
{
	AC_ShaceEnemyController* Controller =
		Cast<AC_ShaceEnemyController>(OwnerComp.GetAIOwner());
	if (Controller)
	{
		Controller->Fire();
	}
	return EBTNodeResult::Succeeded;
}