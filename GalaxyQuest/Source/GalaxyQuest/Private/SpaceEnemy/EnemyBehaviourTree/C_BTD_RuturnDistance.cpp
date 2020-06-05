// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/SpaceEnemy/EnemyBehaviourTree/C_BTD_RuturnDistance.h"

#include "../Public/SpaceEnemy/C_ShaceEnemyController.h"
#include "../Public/SpaceEnemy/C_SpaceEnemy.h"

bool UC_BTD_RuturnDistance::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const {
	
	AC_ShaceEnemyController* Controller = Cast<AC_ShaceEnemyController>(OwnerComp.GetAIOwner());
	if (Controller){
		AC_SpaceEnemy* Enemy= Controller->EnemyShip;
		if (Enemy){
			FVector OriginLocation = Enemy->SpawnerLocation;
			FVector CurLocation = Enemy->GetActorLocation();
			float CurDistacne = (OriginLocation - CurLocation).Size();
			if (CurDistacne > AllowDostance){
				Controller->TurnToReturnState();
			}
		}
	}
	
	return true;
}