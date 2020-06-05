// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/SpaceEnemy/EnemyBehaviourTree/C_BTT_Around.h"

#include "../Public/SpaceEnemy/C_ShaceEnemyController.h"
#include "../Public/SpaceEnemy/C_SpaceEnemy.h"

#include "Kismet/KismetMathLibrary.h"

EBTNodeResult::Type UC_BTT_Around::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	AC_ShaceEnemyController* Controller = Cast<AC_ShaceEnemyController> (OwnerComp.GetAIOwner());
	if (Controller){
		AC_SpaceEnemy* Enemy = Cast<AC_SpaceEnemy>(Controller->GetPawn());
		if (Controller->IsAroundNeedAngle()){
			FVector ResultLocation = (Enemy->GetActorLocation() - Controller->AroundPoint);
			Controller->AroundDirectrion = UKismetMathLibrary::FindLookAtRotation(FVector::ZeroVector, ResultLocation);
			Controller->SetAroundNeedAngle(false);
			Controller->SetKeepAround(true);
		}
		if (Controller->CurAroundTime > Enemy->AroundCostTime) {
			Controller->SetKeepAround(false);
		}
	}
	return EBTNodeResult::Succeeded;
}