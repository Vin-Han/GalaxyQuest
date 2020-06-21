// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/SpaceEnemy/EnemyBehaviourTree/C_BTD_ReturnCheck.h"

#include "../Public/SpaceEnemy/C_ShaceEnemyController.h"
#include "../Public/SpaceEnemy/C_SpaceEnemy.h"

bool UC_BTD_ReturnCheck::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const 
{
	AC_ShaceEnemyController* Controller = Cast<AC_ShaceEnemyController>(OwnerComp.GetAIOwner());
	if (Controller)
	{
		AC_SpaceEnemy* Enemy = Cast<AC_SpaceEnemy> (Controller->EnemyShip);
		if (Enemy)
		{
			if (Controller->GapDirection.Equals(Enemy->GetActorRotation(), AcceptDegree))
			{
				//Controller->bIfPartolKeepRotate = false;
			}
		}
	}
	return true;
}