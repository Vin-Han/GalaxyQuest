// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/SpaceEnemy/EnemyBehaviourTree/C_BTD_ReturnCheck.h"

#include "../Public/SpaceEnemy/C_ShaceEnemyController.h"
#include "../Public/SpaceEnemy/C_SpaceEnemy.h"

#include "BehaviorTree/BlackboardComponent.h"

bool UC_BTD_ReturnCheck::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const {
	AC_ShaceEnemyController* Controller = Cast<AC_ShaceEnemyController>(OwnerComp.GetAIOwner());
	if (Controller){
		UBlackboardComponent* BBCom = Controller->BBCom;
		AC_SpaceEnemy* Enemy = Cast<AC_SpaceEnemy> (Controller->EnemyShip);
		if (Enemy && BBCom){
			float CurDistance = (Enemy->GetActorLocation() -
				BBCom->GetValueAsVector(TEXT("PlayerLocation"))).Size();
			if (CurDistance > AllowDistance){
				//Controller->BackToPatrolState();
			}
		}
	}
	return true;
}