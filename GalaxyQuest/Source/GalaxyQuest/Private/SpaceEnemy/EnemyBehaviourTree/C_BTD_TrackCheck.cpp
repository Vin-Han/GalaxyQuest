// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/SpaceEnemy/EnemyBehaviourTree/C_BTD_TrackCheck.h"

#include "../Public/SpaceEnemy/C_ShaceEnemyController.h"
#include "../Public/SpaceEnemy/C_SpaceEnemy.h"
#include "../public/SpaceEnemy/C_SpaceEnemy_State.h"

#include "BehaviorTree/BlackboardComponent.h"

bool UC_BTD_TrackCheck::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const {
	AC_ShaceEnemyController* Controller = Cast<AC_ShaceEnemyController>(OwnerComp.GetAIOwner());
	if (Controller) {
		AC_SpaceEnemy* Enemy = Controller->EnemyShip;
		if (Enemy && AllowFollowDistance > 0){
			UBlackboardComponent* BBCom = Controller->BBCom;
			FVector TargetLocation = BBCom->GetValueAsVector(TEXT("PlayerLocation"));
			float CurrentDistance = (TargetLocation - Enemy->GetActorLocation()).Size();
			if (CurrentDistance > AllowFollowDistance){
				Controller->BackToPatrolState();
			}
		}
	}
	return true;
}