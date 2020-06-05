#include "../Public/SpaceEnemy/EnemyBehaviourTree/C_BTT_Partal.h"
#include "../Public/SpaceEnemy/C_ShaceEnemyController.h"
#include "../Public/SpaceEnemy/C_SpaceEnemy.h"


EBTNodeResult::Type UC_BTT_Partal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
	AC_ShaceEnemyController* Controller = Cast<AC_ShaceEnemyController>(OwnerComp.GetAIOwner());
	if (Controller && Controller->CurLoadingTime > Controller->ReloadingTime){
		Controller->SetPartolStateReset(true);
	}
	return EBTNodeResult::Succeeded;
}
/*
void UC_BTT_Partal::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds){
	AC_ShaceEnemyController* Controller = Cast<AC_ShaceEnemyController>(OwnerComp.GetAIOwner());
	if (Controller){
		AC_SpaceEnemy* Enemy = Cast<AC_SpaceEnemy>(Controller->GetPawn());
		if (Enemy){
			Controller->CurLoadingTime += DeltaSeconds;
			if (Controller->CurLoadingTime < Enemy->RotateCostTime) {
				Enemy->AddActorWorldRotation(Controller->GapDirection * DeltaSeconds);
			}
			Enemy->AddMovementInput(Enemy->GetActorForwardVector(),
				Enemy->EnemySpeed * DeltaSeconds);
		}
	}
}
*/