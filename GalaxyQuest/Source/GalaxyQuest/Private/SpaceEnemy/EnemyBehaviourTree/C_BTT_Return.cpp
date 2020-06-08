// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/SpaceEnemy/EnemyBehaviourTree/C_BTT_Return.h"

#include "../Public/SpaceEnemy/C_ShaceEnemyController.h"
#include "../Public/SpaceEnemy/C_SpaceEnemy.h"

EBTNodeResult::Type UC_BTT_Return::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) 
{
	
	AC_ShaceEnemyController* Controller = Cast<AC_ShaceEnemyController>(OwnerComp.GetAIOwner());
	if (Controller) 
	{
		AC_SpaceEnemy* Enemy = Controller->EnemyShip;
		if (Enemy) 
		{
			FVector OriginLocation = Enemy->SpawnerLocation;
			FVector CurLocation = Enemy->GetActorLocation();
			float CurDistacne = (OriginLocation - CurLocation).Size();
			if (CurDistacne < AllowDostance) 
			{
				Controller->TurnToPartolState();
			}
		}
	}
	
	return EBTNodeResult::Succeeded;
}