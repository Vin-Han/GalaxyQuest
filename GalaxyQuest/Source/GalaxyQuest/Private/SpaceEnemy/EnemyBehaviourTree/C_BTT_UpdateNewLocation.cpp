#include "../Public/SpaceEnemy/EnemyBehaviourTree/C_BTT_UpdateNewLocation.h"
#include "../Public/SpaceEnemy/C_ShaceEnemyController.h"
#include "../Public/SpaceEnemy/C_SpaceEnemy.h"

#include "Kismet/KismetMathLibrary.h"

EBTNodeResult::Type UC_BTT_UpdateNewLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	AC_ShaceEnemyController* Controller = Cast<AC_ShaceEnemyController>(OwnerComp.GetAIOwner());
	if (Controller){
		if (Controller->bCanReset == false)
			return EBTNodeResult::Failed;
		else{
			AC_SpaceEnemy* Enemy = Cast<AC_SpaceEnemy>(Controller->GetPawn());
			if (Enemy){
				Controller->CurLoadingTime = 0;
				Controller->ReloadingTime = UKismetMathLibrary::RandomFloatInRange(Enemy->RotateCostTime, Enemy->RotateCostTime + Enemy->ReloadMaxTime);
				Controller->GapDirection.Pitch = UKismetMathLibrary::RandomFloatInRange(- Enemy->RotateMaxDegree, Enemy->RotateMaxDegree);
				Controller->GapDirection.Yaw   = UKismetMathLibrary::RandomFloatInRange(- Enemy->RotateMaxDegree, Enemy->RotateMaxDegree);

				Controller->bCanReset = false;
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}