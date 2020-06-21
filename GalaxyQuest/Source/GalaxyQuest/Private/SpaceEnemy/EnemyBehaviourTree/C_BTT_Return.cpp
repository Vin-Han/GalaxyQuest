// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/SpaceEnemy/EnemyBehaviourTree/C_BTT_Return.h"

#include "../Public/SpaceEnemy/C_ShaceEnemyController.h"
#include "../Public/SpaceEnemy/C_SpaceEnemy.h"

#include "Kismet/KismetMathLibrary.h"

EBTNodeResult::Type UC_BTT_Return::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) 
{
	
	AC_ShaceEnemyController* Controller = Cast<AC_ShaceEnemyController>(OwnerComp.GetAIOwner());
	if (Controller) 
	{
		AC_SpaceEnemy* Enemy = Controller->EnemyShip;
		if (Enemy) 
		{
			float CurDistacne = (Enemy->SpawnerLocation - 
				Enemy->GetActorLocation()).Size();

			if (CurDistacne < AllowDistance)
			{
				Controller->TurnToPartolState();
			}

			else if (Controller->bIfReturnKeepRotate)
			{
				FRotator EnemyToSpawner = UKismetMathLibrary::
					FindLookAtRotation(Enemy->GetActorLocation(), Enemy->SpawnerLocation);
				if (EnemyToSpawner.Equals(Enemy->GetActorRotation(), AllowDegree))
				{
					Controller->bIfReturnKeepRotate = false;
				}
				else
				{
					Controller->ReturnTargetDirection = EnemyToSpawner;
				}
			}
		}
	}
	
	return EBTNodeResult::Succeeded;
}