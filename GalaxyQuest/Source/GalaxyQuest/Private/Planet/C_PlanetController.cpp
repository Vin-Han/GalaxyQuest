// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Planet/C_PlanetController.h"

#include "../Public/Planet/C_NormalPlanetPawn.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/Engine.h"

void AC_PlanetController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	/**/
	FRotator TempRotator = FRotator(0, RotationOnce *DeltaTime, 0);
	Planet->PlanetMesh->AddRelativeRotation(TempRotator);

	/**/
	FVector Position = FVector(0,0,Planet->GetActorLocation().Z);

	CurRevolution += RevolutionOnce * DeltaTime;
	if (CurRevolution >= 360) CurRevolution = 0;

	if ( 89.9 < CurRevolution && CurRevolution < 90.1){
		Position.Y = Planet->OvalB;
	}
	else if (269.9 < CurRevolution && CurRevolution < 270.1){
		Position.Y = - Planet->OvalB;
	}
	else if ( 90 < CurRevolution && CurRevolution < 270 ){
		float temp = pow((Planet->OvalB2 + Planet->OvalA2 * pow(tan(CurRevolution * 3.14 / 180.0), 2)), 0.5);
		Position.X = -((Planet->OvalA * Planet->OvalB) / temp);
		Position.Y = -((Planet->OvalA * Planet->OvalB / temp * tan(CurRevolution * 3.14 / 180.0)) );
	}
	else {
		float temp = pow((Planet->OvalB2 + Planet->OvalA2 * pow(tan(CurRevolution * 3.14 / 180.0), 2)), 0.5);
		Position.X = (Planet->OvalA * Planet->OvalB) / temp;
		Position.Y = (Planet->OvalA * Planet->OvalB / temp * tan(CurRevolution * 3.14 / 180.0)) ;
	}

	Planet->CollisionCom->SetRelativeLocation(Position);

}

void AC_PlanetController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);

	Planet = Cast<AC_NormalPlanetPawn>(InPawn);
	if (Planet == NULL) { UE_LOG(LogTemp, Warning, TEXT("Planet Cast Fasiled"));}
	else {
		RotationOnce = 360 / (Planet->SelfRotation / 24);
		RevolutionOnce = 360 / Planet->Revolution;
		CurRevolution = Planet->CurDegree;
	}
}