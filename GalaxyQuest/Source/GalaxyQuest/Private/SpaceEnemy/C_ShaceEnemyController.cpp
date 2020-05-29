#include "../Public/SpaceEnemy/C_ShaceEnemyController.h"
#include "../Public/SpaceEnemy/C_SpaceEnemy.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Kismet/KismetMathLibrary.h"

AC_ShaceEnemyController::AC_ShaceEnemyController() {
	BTCom = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree"));
	BBCom = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoard"));
}

void AC_ShaceEnemyController::OnPossess(APawn* InPawn){
	Super::OnPossess(InPawn);
	EnemyShip = Cast<AC_SpaceEnemy>(InPawn);
	if (EnemyShip){
		EnemyShip->RotateMaxDegree	= FMath::Max(0.0f, EnemyShip->RotateMaxDegree);
		EnemyShip->RotateCostTime	= FMath::Max(0.0f, EnemyShip->RotateCostTime);
		EnemyShip->ReloadMaxTime	= FMath::Max(0.0f, EnemyShip->ReloadMaxTime);
		EnemyShip->PartolSpeed		= FMath::Max(0.0f, EnemyShip->PartolSpeed);

		bCanReset = true;

		CurLoadingTime = 0.f;
		GapDirection = FRotator::ZeroRotator;
		ReloadingTime = UKismetMathLibrary::RandomFloatInRange(EnemyShip->RotateCostTime,
											EnemyShip->RotateCostTime + EnemyShip->ReloadMaxTime);
	}

	if (EnemyShip){
		EnemyShip->TrackSpeed		= FMath::Max(0.0f, EnemyShip->TrackSpeed);
		EnemyShip->TrackCostTime	= FMath::Max(0.0f, EnemyShip->TrackCostTime);
		EnemyShip->AllowDistance	= FMath::Max(0.0f, EnemyShip->AllowDistance);
		bCanMove = true;
	}

	if (EnemyShip){
		EnemyShip->AroundSpeed = FMath::Max(0.0f, EnemyShip->AroundSpeed);
		EnemyShip->AroundCostTime = FMath::Max(0.0f, EnemyShip->AroundCostTime);

		bKeepAround = false;
		bNeedAngle = true;
		CurAroundTime = 0;
	}

	if (EnemyShip && EnemyShip->BehaviorTree){
		BBCom->InitializeBlackboard(*(EnemyShip->BehaviorTree->BlackboardAsset));
		BTCom->StartTree(*(EnemyShip->BehaviorTree));
	}
}

void AC_ShaceEnemyController::Tick(float DeltaSeconds){

	if (EnemyShip->CurrentState == EnemyState::AROUND)
		ShipAroundMove(DeltaSeconds);

	if (EnemyShip->CurrentState == EnemyState::PATROL)
		ShipPartolMove(DeltaSeconds);

	if (EnemyShip->CurrentState == EnemyState::TRACK)
		ShipTrackMove(DeltaSeconds);

}

void AC_ShaceEnemyController::ShipPartolMove(float DeltaSeconds){
	CurLoadingTime += DeltaSeconds;
	if (CurLoadingTime < EnemyShip->RotateCostTime){
		EnemyShip->AddActorWorldRotation(GapDirection * DeltaSeconds);
	}
	EnemyShip->AddMovementInput(EnemyShip->GetActorForwardVector(), 
								EnemyShip->PartolSpeed * DeltaSeconds);
}

void AC_ShaceEnemyController::ShipTrackMove(float DeltaSeconds){
	EnemyShip->SetActorRotation(EnemyShip->GetActorRotation() + 
								DeltaSeconds * (TargetDirection  - EnemyShip->GetActorRotation()));
	if (bCanMove)
		EnemyShip->AddMovementInput(EnemyShip->GetActorForwardVector(),
				EnemyShip->TrackSpeed * DeltaSeconds / EnemyShip->TrackCostTime);

}

void AC_ShaceEnemyController::ShipAroundMove(float DeltaSeconds){
	CurAroundTime += DeltaSeconds;

	if (bKeepAround)
		EnemyShip->SetActorRotation(EnemyShip->GetActorRotation() +
			DeltaSeconds * AroundDirectrion *(1/EnemyShip->AroundCostTime));
	EnemyShip->AddMovementInput(EnemyShip->GetActorForwardVector(),
		EnemyShip->AroundSpeed * DeltaSeconds );
}