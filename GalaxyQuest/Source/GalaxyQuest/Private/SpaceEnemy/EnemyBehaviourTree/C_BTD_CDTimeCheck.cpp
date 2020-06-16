// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/SpaceEnemy/EnemyBehaviourTree/C_BTD_CDTimeCheck.h"
#include "../Public/SpaceEnemy/C_ShaceEnemyController.h"

bool UC_BTD_CDTimeCheck::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const 
{
	AC_ShaceEnemyController* Controller =
		Cast<AC_ShaceEnemyController>(OwnerComp.GetAIOwner());
	if (Controller)
	{
		if (Controller->EnemyBulletItem.BulletClass &&
			Controller->EnemyBulletItem.CurrentLoadingTime <= 0.0f)
		{
			return true;
		}
		return false;
	}
	return false;
}