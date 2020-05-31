#include "../Public/SpaceEnemy/C_ShaceEnemyController.h"
#include "../Public/SpaceEnemy/C_SpaceEnemy.h"
#include "../Public/SpaceEnemy/C_SpaceEnemySpawner.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "../Public/Planet/C_NormalPlanetPawn.h"
#include "../Public/Character/C_SystemCharacter.h"

#include "Components/BoxComponent.h"

#include "TimerManager.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

AC_ShaceEnemyController::AC_ShaceEnemyController() {
	BTCom = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree"));
	BBCom = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoard"));
}

void AC_ShaceEnemyController::BeginPlay()
{
	Super::BeginPlay();
	if (EnemyShip){
		EnemyShip->CollisionCom->OnComponentBeginOverlap.AddDynamic(this,&AC_ShaceEnemyController::EnemyBlock);
		EnemyShip->TriggerCom->OnComponentBeginOverlap.AddDynamic(this, &AC_ShaceEnemyController::TriggerOverlap);
	}
}

void AC_ShaceEnemyController::OnPossess(APawn* InPawn){
	Super::OnPossess(InPawn);
	EnemyShip = Cast<AC_SpaceEnemy>(InPawn);
	if (EnemyShip){
		EnemyShip->RotateMaxDegree	= FMath::Max(0.0f, EnemyShip->RotateMaxDegree);
		EnemyShip->RotateCostTime	= FMath::Max(0.0f, EnemyShip->RotateCostTime);
		EnemyShip->ReloadMaxTime	= FMath::Max(0.0f, EnemyShip->ReloadMaxTime);
		EnemyShip->PartolSpeed		= FMath::Max(0.0f, EnemyShip->PartolSpeed);

		InilializePatrol();
	}

	if (EnemyShip){
		EnemyShip->TrackSpeed		= FMath::Max(0.0f, EnemyShip->TrackSpeed);
		EnemyShip->TrackCostTime	= FMath::Max(0.0f, EnemyShip->TrackCostTime);
		EnemyShip->AllowDistance	= FMath::Max(0.0f, EnemyShip->AllowDistance);

		InitializeTrack();
	}

	if (EnemyShip){
		EnemyShip->AroundSpeed = FMath::Max(0.0f, EnemyShip->AroundSpeed);
		EnemyShip->AroundCostTime = FMath::Max(0.0f, EnemyShip->AroundCostTime);

		OriginalState = EnemyState::PATROL;
		InitializeAround();
	}

	if (EnemyShip){
		ReturnSpeed = 15;
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

	if (EnemyShip->CurrentState == EnemyState::RETURN)
		ShipReturnMove(DeltaSeconds);
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

void AC_ShaceEnemyController::ChangeToReturnMode(){
	
	if (EnemyShip->CurrentState != EnemyState::AROUND){
		EnemyShip->CurrentState = EnemyState::RETURN;
		EnemyShip->SetActorRotation(UKismetMathLibrary::FindLookAtRotation
		(EnemyShip->GetActorLocation(), EnemyShip->SpawnerLocation)
		);
	}
	
}

void AC_ShaceEnemyController::ShipReturnMove(float DeltaSeconds){
	EnemyShip->AddMovementInput(EnemyShip->GetActorForwardVector(),
		ReturnSpeed * DeltaSeconds);
}

void AC_ShaceEnemyController::EnemyBlock(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool FromSweep, const FHitResult& HitRusult)
{
	if (Cast<AC_NormalPlanetPawn>(OtherActor)){
		BlockWithPlanet();
	}
	if (Cast<AC_SystemCharacter>(OtherActor)) {
		BlockWithShip();
	}
}

void AC_ShaceEnemyController::TriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool FromSweep, const FHitResult& HitRusult)
{
	if (Cast<AC_NormalPlanetPawn>(OtherActor)) {
		OverlapWithPlanet();
	}
	if (Cast<AC_SystemCharacter>(OtherActor)) {
		OverlapWithShip();
	}
}

void AC_ShaceEnemyController::BlockWithShip(){
	//EnemyShip->OnDestory();
	EnemyShip->Destroy();
}

void AC_ShaceEnemyController::BlockWithPlanet(){
	//EnemyShip->OnDestory();
	EnemyShip->Destroy();
}

void AC_ShaceEnemyController::OverlapWithShip(){
	if (EnemyShip->CurrentState == EnemyState::PATROL){
		EnemyShip->CurrentState = EnemyState::TRACK;
		InitializeTrack();
	}
}

void AC_ShaceEnemyController::OverlapWithPlanet(){
	//UE_LOG(LogTemp, Warning, TEXT("Overlap"));
	EnemyShip->CurrentState = EnemyState::AROUND;
	InitializeAround();
	GetWorld()->GetTimerManager().SetTimer(TH_StateReverse, this, &AC_ShaceEnemyController::BackToOriginState, 1,
		false, (EnemyShip->AroundCostTime + 2.0f));
}

void AC_ShaceEnemyController::BackToOriginState(){
	
	if (OriginalState == EnemyState::TRACK){
		EnemyShip->CurrentState = EnemyState::TRACK;
		InitializeTrack();
	}
	else if (OriginalState == EnemyState::PATROL){
		EnemyShip->CurrentState = EnemyState::PATROL;
		InilializePatrol();
	}
	else if (OriginalState == EnemyState::RETURN) {
		EnemyShip->CurrentState = EnemyState::RETURN;
		ChangeToReturnMode();
	}
}

void AC_ShaceEnemyController::InitializeTrack(){
	bCanMove = true;
}

void AC_ShaceEnemyController::InitializeAround(){
	bKeepAround = false;
	bNeedAngle = true;
	CurAroundTime = 0;
	if (EnemyShip->CurrentState != EnemyState::AROUND){
		OriginalState = EnemyShip->CurrentState;
	}
}

void AC_ShaceEnemyController::InilializePatrol(){
	bCanReset = true;
	CurLoadingTime = 0.f;
	GapDirection = FRotator::ZeroRotator;
	ReloadingTime = UKismetMathLibrary::RandomFloatInRange(EnemyShip->RotateCostTime,
		EnemyShip->RotateCostTime + EnemyShip->ReloadMaxTime);

}

void AC_ShaceEnemyController::BackToPatrolState(){
	EnemyShip->CurrentState = EnemyState::PATROL;
	InilializePatrol();
}
