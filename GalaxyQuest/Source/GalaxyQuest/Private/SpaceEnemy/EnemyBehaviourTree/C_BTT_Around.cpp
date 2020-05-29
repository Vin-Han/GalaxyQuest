// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/SpaceEnemy/EnemyBehaviourTree/C_BTT_Around.h"

#include "../Public/SpaceEnemy/C_ShaceEnemyController.h"
#include "../Public/SpaceEnemy/C_SpaceEnemy.h"

#include "Kismet/KismetMathLibrary.h"

EBTNodeResult::Type UC_BTT_Around::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	AC_ShaceEnemyController* Controller = Cast<AC_ShaceEnemyController> (OwnerComp.GetAIOwner());
	if (Controller){
		AC_SpaceEnemy* Enemy = Cast<AC_SpaceEnemy>(Controller->GetPawn());
		if (Controller->bNeedAngle == true){
			FVector ResultLocation = (Enemy->GetActorLocation() - Controller->AroundPoint);
			Controller->AroundDirectrion = UKismetMathLibrary::FindLookAtRotation(FVector::ZeroVector, ResultLocation);
			Controller->bNeedAngle = false;
			Controller->bKeepAround = true;
		}
		if (Controller->CurAroundTime > Enemy->AroundCostTime) {
			Controller->bKeepAround = false;
		}
	}
	return EBTNodeResult::Succeeded;
}