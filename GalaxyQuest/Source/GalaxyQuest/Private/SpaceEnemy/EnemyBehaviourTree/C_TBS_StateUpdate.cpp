// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/SpaceEnemy/EnemyBehaviourTree/C_TBS_StateUpdate.h"

#include "../Public/SpaceEnemy/C_ShaceEnemyController.h"

#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void UC_TBS_StateUpdate::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
	//Bboard->SetValueAsObject(TEXT("SelfActor"), Monster);
	AC_ShaceEnemyController* EnemyController = Cast<AC_ShaceEnemyController>(OwnerComp.GetAIOwner());
	if (EnemyController){
		EnemyController->BBCom->SetValueAsVector(TEXT("PlayerLocation"),
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn()->GetActorLocation());
	}
}