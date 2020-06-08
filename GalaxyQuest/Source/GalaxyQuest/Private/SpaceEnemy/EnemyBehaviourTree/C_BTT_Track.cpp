#include "../Public/SpaceEnemy/EnemyBehaviourTree/C_BTT_Track.h"

#include "../Public/SpaceEnemy/C_ShaceEnemyController.h"
#include "../Public/SpaceEnemy/C_SpaceEnemy.h"

#include "Kismet/KismetMathLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UC_BTT_Track::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) 
{

	AC_ShaceEnemyController* Controller = Cast<AC_ShaceEnemyController>(OwnerComp.GetAIOwner());
	if (Controller) 
	{
		AC_SpaceEnemy* Enemy = Cast<AC_SpaceEnemy>(Controller->GetPawn());
		if (Enemy)
		{
			FVector PlayerLocation = Controller->BBCom->GetValueAsVector(TEXT("PlayerLocation"));
			Controller->TargetDirection = UKismetMathLibrary::FindLookAtRotation(Enemy->GetActorLocation(), PlayerLocation);

			float Distance = FVector(Enemy->GetActorLocation() - PlayerLocation).Size();
			Controller->SetTrackCanMove(Distance < Enemy->AllowDistance ? 0 : 1);
		}
	}
	return EBTNodeResult::Succeeded;
}