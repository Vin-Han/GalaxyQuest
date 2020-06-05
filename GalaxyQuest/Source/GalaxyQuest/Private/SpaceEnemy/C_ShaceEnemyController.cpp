#include "../Public/SpaceEnemy/C_ShaceEnemyController.h"
#include "../Public/SpaceEnemy/C_SpaceEnemy.h"
#include "../Public/SpaceEnemy/C_SpaceEnemySpawner.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "../Public/Planet/C_NormalPlanetPawn.h"
#include "../Public/Character/C_SystemCharacter.h"

#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/ProgressBar.h"

#include "TimerManager.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

AC_ShaceEnemyController::AC_ShaceEnemyController() 
{
	BTCom = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree"));
	BBCom = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoard"));
}

void AC_ShaceEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	EnemyShip = Cast<AC_SpaceEnemy>(InPawn);

	InitializeEnemyData();
	InitializeEvent();
	InitializeControllerData();
	InitializeEnemyHealth();
	if (EnemyShip)
	{
		InilializePatrol();
		InitializeTrack();
		InitializeAround();
		IniilalizeReturn();
	}

}

#pragma region Initialize State
void AC_ShaceEnemyController::InitializeEnemyData()
{
	if (EnemyShip)
	{
		EnemyShip->RotateMaxDegree = FMath::Max(0.0f, EnemyShip->RotateMaxDegree);
		EnemyShip->RotateCostTime = FMath::Max(0.0f, EnemyShip->RotateCostTime);
		EnemyShip->ReloadMaxTime = FMath::Max(0.0f, EnemyShip->ReloadMaxTime);
		EnemyShip->PartolSpeed = FMath::Max(0.0f, EnemyShip->PartolSpeed);

		EnemyShip->TrackSpeed = FMath::Max(0.0f, EnemyShip->TrackSpeed);
		EnemyShip->TrackCostTime = FMath::Max(0.0f, EnemyShip->TrackCostTime);
		EnemyShip->AllowDistance = FMath::Max(0.0f, EnemyShip->AllowDistance);

		EnemyShip->AroundSpeed = FMath::Max(0.0f, EnemyShip->AroundSpeed);
		EnemyShip->AroundCostTime = FMath::Max(0.0f, EnemyShip->AroundCostTime);

	}
}

void AC_ShaceEnemyController::InitializeEvent()
{
	if (EnemyShip)
	{
		if (EnemyShip->CollisionCom)
			EnemyShip->CollisionCom->OnComponentBeginOverlap.AddDynamic(this, &AC_ShaceEnemyController::EnemyBlock);
		if (EnemyShip->TriggerCom)
			EnemyShip->TriggerCom->OnComponentBeginOverlap.AddDynamic(this, &AC_ShaceEnemyController::TriggerOverlap);
	}
}

void AC_ShaceEnemyController::InitializeControllerData()
{
	if (EnemyShip)
	{
		OriginalState = EnemyState::PATROL;
		ReturnSpeed = 15;
	}
	if (EnemyShip && EnemyShip->BehaviorTree)
	{
		BBCom->InitializeBlackboard(*(EnemyShip->BehaviorTree->BlackboardAsset));
		BTCom->StartTree(*(EnemyShip->BehaviorTree));
	}
}

void AC_ShaceEnemyController::InitializeEnemyHealth()
{
	if (EnemyShip)
	{
		EnemyCurHP = EnemyShip->EnemyTolHP;
	}
}

void AC_ShaceEnemyController::InitializeTrack() 
{
	bCanMove = true;

}

void AC_ShaceEnemyController::InitializeAround() 
{
	bKeepAround = false;
	bNeedAngle = true;
	CurAroundTime = 0;
	if (EnemyShip->CurrentState != EnemyState::AROUND) 
	{
		OriginalState = EnemyShip->CurrentState;
	}

}

void AC_ShaceEnemyController::InilializePatrol() 
{
	bCanReset = true;
	CurLoadingTime = 0.f;
	GapDirection = FRotator::ZeroRotator;
	ReloadingTime = UKismetMathLibrary::RandomFloatInRange(EnemyShip->RotateCostTime,
		EnemyShip->RotateCostTime + EnemyShip->ReloadMaxTime);

}

void AC_ShaceEnemyController::IniilalizeReturn()
{
}

#pragma endregion

void AC_ShaceEnemyController::BackToOriginState() 
{

	if (OriginalState == EnemyState::TRACK)
	{
		TurnToTrackState();
	}
	else if (OriginalState == EnemyState::PATROL)
	{
		TurnToPartolState();
	}
	else if (OriginalState == EnemyState::RETURN)
	{
		TurnToReturnState();
	}

}

#pragma region State Change
void AC_ShaceEnemyController::TurnToAroundState()
{
	InitializeAround();
	EnemyShip->CurrentState = EnemyState::AROUND;
	GetWorld()->GetTimerManager().SetTimer(TH_StateReverse, this, &AC_ShaceEnemyController::BackToOriginState, 1,
		false, (EnemyShip->AroundCostTime + 2.0f));
}

void AC_ShaceEnemyController::TurnToReturnState()
{
	EnemyShip->CurrentState = EnemyState::RETURN;
	EnemyShip->SetActorRotation(UKismetMathLibrary::FindLookAtRotation
	(EnemyShip->GetActorLocation(), EnemyShip->SpawnerLocation));
}

void AC_ShaceEnemyController::TurnToPartolState()
{
	EnemyShip->CurrentState = EnemyState::PATROL;
	InilializePatrol();
}

void AC_ShaceEnemyController::TurnToTrackState()
{
	EnemyShip->CurrentState = EnemyState::TRACK;
	InitializeTrack();
}

void AC_ShaceEnemyController::ReSetPartolInfor(float newReloadTime, FRotator newRotator, bool isCurTimeReset)
{
	ReloadingTime = newReloadTime;
	GapDirection = newRotator;
	if (isCurTimeReset)
	{
		CurLoadingTime = 0;
	}

}

#pragma endregion

void AC_ShaceEnemyController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateMovement(DeltaSeconds);
	UpdateEnemyHP();
}

#pragma region Update Movement
void AC_ShaceEnemyController::UpdateMovement(float DeltaTime)
{
	if (EnemyShip->CurrentState == EnemyState::PATROL)
		ShipPartolMove(DeltaTime);
	else if (EnemyShip->CurrentState == EnemyState::AROUND)
		ShipAroundMove(DeltaTime);
	else if (EnemyShip->CurrentState == EnemyState::RETURN)
		ShipReturnMove(DeltaTime);
	else if (EnemyShip->CurrentState == EnemyState::TRACK)
		ShipTrackMove(DeltaTime);

}

void AC_ShaceEnemyController::ShipPartolMove(float DeltaSeconds) 
{
	CurLoadingTime += DeltaSeconds;
	if (CurLoadingTime < EnemyShip->RotateCostTime) 
	{
		EnemyShip->AddActorWorldRotation(GapDirection * DeltaSeconds);
	}
	EnemyShip->AddMovementInput(EnemyShip->GetActorForwardVector(),
		EnemyShip->PartolSpeed * DeltaSeconds);

}

void AC_ShaceEnemyController::ShipTrackMove(float DeltaSeconds) 
{
	EnemyShip->SetActorRotation(EnemyShip->GetActorRotation() +
		DeltaSeconds * (TargetDirection - EnemyShip->GetActorRotation()));
	if (bCanMove) 
	{
		EnemyShip->AddMovementInput(EnemyShip->GetActorForwardVector(),
			EnemyShip->TrackSpeed * DeltaSeconds / EnemyShip->TrackCostTime);
	}

}

void AC_ShaceEnemyController::ShipAroundMove(float DeltaSeconds)
{
	CurAroundTime += DeltaSeconds;
	if (bKeepAround)
	{
		EnemyShip->SetActorRotation(EnemyShip->GetActorRotation() +
			AroundDirectrion * (DeltaSeconds / EnemyShip->AroundCostTime));
	}
	EnemyShip->AddMovementInput(EnemyShip->GetActorForwardVector(),
		EnemyShip->AroundSpeed * DeltaSeconds);

}

void AC_ShaceEnemyController::ShipReturnMove(float DeltaSeconds) 
{
	EnemyShip->AddMovementInput(EnemyShip->GetActorForwardVector(),
		ReturnSpeed * DeltaSeconds);
}

#pragma endregion

void AC_ShaceEnemyController::EnemyBlock(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool FromSweep, const FHitResult& HitRusult)
{
	if (Cast<AC_NormalPlanetPawn>(OtherActor))
	{
		BlockWithPlanet();
	}
	if (Cast<AC_SystemCharacter>(OtherActor)) 
	{
		BlockWithShip();
	}

}

void AC_ShaceEnemyController::TriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool FromSweep, const FHitResult& HitRusult)
{
	if (Cast<AC_NormalPlanetPawn>(OtherActor)) 
	{
		OverlapWithPlanet();
	}
	if (Cast<AC_SystemCharacter>(OtherActor)) 
	{
		OverlapWithShip();
	}

}

#pragma region Overlap Event
void AC_ShaceEnemyController::BlockWithShip() 
{
	if (EnemyShip->ParentSpawner) 
	{
		EnemyShip->OnDestory();
	}
	else 
	{
		EnemyShip->Destroy();
	}

}

void AC_ShaceEnemyController::BlockWithPlanet() 
{
	if (EnemyShip->ParentSpawner) 
	{
		EnemyShip->OnDestory();
	}
	else 
	{
		EnemyShip->Destroy();
	}

}

void AC_ShaceEnemyController::OverlapWithShip() 
{
	if (EnemyShip->CurrentState == EnemyState::PATROL) 
	{
		TurnToTrackState();
	}
}

void AC_ShaceEnemyController::OverlapWithPlanet() 
{
	TurnToAroundState();
}

#pragma endregion


#pragma region Enemy Health
void AC_ShaceEnemyController::UpdateEnemyHP()
{
	if (EnemyShip->EnemyBloodBar &&
		EnemyShip->EnemyBlood)
	{
		if (EnemyShip->CurrentState != EnemyState::TRACK &&
			EnemyCurHP == EnemyShip->EnemyTolHP)
		{
			EnemyShip->EnemyBlood->SetVisibility(false);
		}
		else
		{
			EnemyShip->EnemyBlood->SetVisibility(true);
		}

		float tempPercent = FMath::Max(0.f, EnemyCurHP / EnemyShip->EnemyTolHP);
		EnemyShip->EnemyBloodBar->SetPercent(tempPercent);
	}
}

#pragma endregion