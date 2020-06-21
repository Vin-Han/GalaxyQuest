#include "../Public/SpaceEnemy/C_ShaceEnemyController.h"
#include "../Public/SpaceEnemy/C_SpaceEnemy.h"
#include "../Public/SpaceEnemy/C_SpaceEnemySpawner.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "../Public/Planet/C_NormalPlanetPawn.h"
#include "../Public/Character/C_SystemCharacter.h"

#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/ProgressBar.h"

#include "TimerManager.h"
#include "Engine/World.h"

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
	InitializeEnemyBullet();
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
		EnemyShip->AllowDistance = FMath::Max(0.0f, EnemyShip->AllowDistance);

	}
}

void AC_ShaceEnemyController::InitializeEvent()
{
	if (EnemyShip)
	{
		if (EnemyShip->CollisionCom)
		{
			EnemyShip->CollisionCom->OnComponentBeginOverlap.AddDynamic(this, &AC_ShaceEnemyController::EnemyBlock);
		}
		if (EnemyShip->TriggerCom)
		{
			EnemyShip->TriggerCom->OnComponentBeginOverlap.AddDynamic(this, &AC_ShaceEnemyController::TriggerOverlap);
			EnemyShip->TriggerCom->OnComponentEndOverlap.AddDynamic(this,&AC_ShaceEnemyController::TriggerEndOverlap);
		}
	}
}

void AC_ShaceEnemyController::InitializeControllerData()
{
	if (EnemyShip)
	{
		OriginalState = EnemyState::PATROL;
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
	}
}

void AC_ShaceEnemyController::InitializeEnemyBullet()
{
	if (EnemyShip && EnemyShip->EnemyBullet)
	{
		EnemyBulletItem = FBulletBagItem();
		EnemyBulletItem.BulletClass = EnemyShip->EnemyBullet;
		EnemyBulletItem.CurrentLoadingTime = 
			EnemyBulletItem.BulletClass.GetDefaultObject()->BulletLoadingTime;
	}
	//UE_LOG(LogTemp, Warning, TEXT("Bullet have instance"));
}

void AC_ShaceEnemyController::InitializeTrack() 
{
	bIfTrackKeepMove = true;
}

void AC_ShaceEnemyController::InitializeAround() 
{
	bIsAroudFinished = true;
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
	bIfReturnKeepRotate = true;
}

#pragma endregion

#pragma region State Change
void AC_ShaceEnemyController::TurnToAroundState(FVector NewAroundPoint)
{
	InitializeAround();
	EnemyShip->CurrentState = EnemyState::AROUND;
	AroundPoint = NewAroundPoint;
	/*
	GetWorld()->GetTimerManager().SetTimer(TH_StateReverse, this, &AC_ShaceEnemyController::BackToOriginState, 1,
		false, (EnemyShip->AroundCostTime + 2.0f));
	*/
}

void AC_ShaceEnemyController::TurnToReturnState()
{
	EnemyShip->CurrentState = EnemyState::RETURN;
	IniilalizeReturn();
	/*
	EnemyShip->SetActorRotation(UKismetMathLibrary::FindLookAtRotation
		(EnemyShip->GetActorLocation(), EnemyShip->SpawnerLocation));
	*/
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

void AC_ShaceEnemyController::BackToOriginState()
{
	bIsAroudFinished = true;
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

#pragma endregion

void AC_ShaceEnemyController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateMovement(DeltaSeconds);
	UpdateEnemyHP();
	UpdateBullet(DeltaSeconds);
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
	if (bIfTrackKeepMove)
	{
		EnemyShip->AddMovementInput(EnemyShip->GetActorForwardVector(),
			EnemyShip->TrackSpeed * DeltaSeconds);
	}

}

void AC_ShaceEnemyController::ShipAroundMove(float DeltaSeconds)
{
	EnemyShip->SetActorRotation(EnemyShip->GetActorRotation() +
		DeltaSeconds * (AroundTargetDirection - EnemyShip->GetActorRotation()));
	EnemyShip->AddMovementInput(EnemyShip->GetActorForwardVector(),
		EnemyShip->PartolSpeed * DeltaSeconds);
}

void AC_ShaceEnemyController::ShipReturnMove(float DeltaSeconds) 
{
	if (bIfReturnKeepRotate)
	{
		EnemyShip->SetActorRotation(EnemyShip->GetActorRotation() +
			DeltaSeconds * (ReturnTargetDirection - EnemyShip->GetActorRotation()));
	}
	EnemyShip->AddMovementInput(EnemyShip->GetActorForwardVector(),
		EnemyShip->PartolSpeed * DeltaSeconds);
}

#pragma endregion

void AC_ShaceEnemyController::EnemyBlock(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool FromSweep, const FHitResult& HitRusult)
{
	if (OverlappedComponent->IsA<UBoxComponent>())
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
}

void AC_ShaceEnemyController::TriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool FromSweep, const FHitResult& HitRusult)
{
	if (Cast<AC_NormalPlanetPawn>(OtherActor)) 
	{
		OverlapWithPlanet(OtherActor);
	}
	if (Cast<AC_SystemCharacter>(OtherActor)) 
	{
		OverlapWithShip();
	}
}

void AC_ShaceEnemyController::TriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex)
{
	if (Cast<AC_NormalPlanetPawn>(OtherActor))
	{
		EndOverlapWithPlanet();
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

void AC_ShaceEnemyController::OverlapWithPlanet(AActor* OtherActor)
{
	AC_NormalPlanetPawn* AroundPlanet = Cast<AC_NormalPlanetPawn>(OtherActor);
	if (AroundPlanet)
	{
		TurnToAroundState(AroundPlanet->CollisionCom->GetComponentLocation());
	}
}

void AC_ShaceEnemyController::EndOverlapWithPlanet()
{
	BackToOriginState();
}

void AC_ShaceEnemyController::OverlapWithShip() 
{
	if (EnemyShip->CurrentState == EnemyState::PATROL) 
	{
		TurnToTrackState();
	}
}

#pragma endregion

#pragma region Enemy Health
void AC_ShaceEnemyController::UpdateEnemyHP()
{
	if (EnemyShip->EnemyCurHP == 0)
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
	if (EnemyShip->EnemyBloodBar &&
		EnemyShip->EnemyBlood)
	{
		if (EnemyShip->CurrentState != EnemyState::TRACK &&
			EnemyShip->EnemyCurHP == EnemyShip->EnemyTolHP)
		{
			EnemyShip->EnemyBlood->SetVisibility(false);
		}
		else
		{
			EnemyShip->EnemyBlood->SetVisibility(true);
		}

		float tempPercent = FMath::Max(0.f, EnemyShip->EnemyCurHP / EnemyShip->EnemyTolHP);
		EnemyShip->EnemyBloodBar->SetPercent(tempPercent);
	}
}



#pragma endregion

#pragma region Enemy Fire
void AC_ShaceEnemyController::Fire()
{
	if (EnemyBulletItem.BulletClass)
	{
		FVector spawnLocation = EnemyShip->GetActorLocation();
		GetWorld()->SpawnActor(EnemyBulletItem.BulletClass,&spawnLocation, &FRotator::ZeroRotator);
		EnemyBulletItem.CurrentLoadingTime = 
			EnemyBulletItem.BulletClass.GetDefaultObject()->BulletLoadingTime;
	}
}

void AC_ShaceEnemyController::UpdateBullet(float DeltaSeconds)
{
	if (EnemyBulletItem.CurrentLoadingTime > 0.0f)
	{
		EnemyBulletItem.CurrentLoadingTime -= DeltaSeconds;
	}
}

#pragma endregion

