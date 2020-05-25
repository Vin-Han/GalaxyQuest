#include "../Public/Planet/C_PlanetController.h"

#include "../Public/Planet/C_NormalPlanetPawn.h"
#include "../Public/Widget/C_StarIntroduce_UI.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

void AC_PlanetController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);

}

void AC_PlanetController::BeginPlay(){
	Super::BeginPlay();
	Planet = Cast<AC_NormalPlanetPawn>(GetPawn());
	if (Planet == NULL) { UE_LOG(LogTemp, Warning, TEXT("Planet Exchange Failed")) }
	else {
		InitializeOval();
		InitializeOffsetLocation();
		InitializeOrbit();
		InitializePlanet();
	}
}

void AC_PlanetController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	//Self Tilt Rotation
	float PitchCurrent = Planet->PlanetMesh->GetRelativeRotation().Pitch;
	if (PitchCurrent < -TotalSelfTilt) bIsClockWise = true;
	else if (PitchCurrent > TotalSelfTilt) bIsClockWise = false;

	FRotator TiltRotation = bIsClockWise ? FRotator(SelfTilt * DeltaTime, 0, 0) : FRotator(-SelfTilt * DeltaTime, 0, 0);
	Planet->PlanetMesh->AddRelativeRotation(TiltRotation);

	//Self Rotation
	FRotator SelfRotation = FRotator(0, SelfRotaion * DeltaTime, 0);
	Planet->PlanetMesh->AddLocalRotation(SelfRotation);

	//Relative Oval Revulotion
	FVector NewPosition = FVector::ZeroVector;
	CurrentRevolution += RelativeRevolution * DeltaTime;
	if (CurrentRevolution >= 360) CurrentRevolution = 0;

	if (89.8 < CurrentRevolution && CurrentRevolution < 90.2)
		NewPosition.Y = OvalB;
	else if (269.8 < CurrentRevolution && CurrentRevolution < 270.2)
		NewPosition.Y = -OvalB;
	else if (90 < CurrentRevolution && CurrentRevolution < 270) {
		float temp = pow((OvalB2 + OvalA2 * pow(tan(CurrentRevolution * 3.14 / 180.0), 2)), 0.5);
		NewPosition.X = -((OvalA * OvalB) / temp);
		NewPosition.Y = -((OvalA * OvalB / temp * tan(CurrentRevolution * 3.14 / 180.0)));
	}
	else {
		float temp = pow((OvalB2 + OvalA2 * pow(tan(CurrentRevolution * 3.14 / 180.0), 2)), 0.5);
		NewPosition.X = (OvalA * OvalB) / temp;
		NewPosition.Y = (OvalA * OvalB / temp * tan(CurrentRevolution * 3.14 / 180.0));
	}
	Planet->CollisionCom->SetRelativeRotation(FRotator(0, CurrentRevolution, 0));
	Planet->CollisionCom->SetRelativeLocation(NewPosition);
	Planet->BlockCom->SetRelativeLocation(NewPosition);
}

void AC_PlanetController::InitializeOval() {
	OvalA = (Planet->CloseDistance + Planet->FarDistance) / 2;
	OvalC = (Planet->FarDistance - Planet->CloseDistance) / 2;
	OvalA2 = pow(OvalA, 2);
	OvalB2 = OvalA2 - pow(OvalC, 2);
	OvalB = pow(OvalB2, 0.5);
}

void AC_PlanetController::InitializeOffsetLocation() {
	if (Planet->RevolutionTarget) {
		OvalLocation = FVector(OvalC, 0, 0) + Planet->RevolutionTarget->GetActorLocation();
	}
	else OvalLocation = FVector(OvalC, 0, 0);
}

void AC_PlanetController::InitializeOrbit() {
	Planet->OrbitMesh->SetWorldScale3D(FVector(OvalA / 100, OvalB / 100, 100));
	Planet->SetActorLocation(OvalLocation);
	Planet->SetActorRotation(FRotator(Planet->RevolutionTilt, 0, 0));
}

void AC_PlanetController::InitializePlanet() {
	if (Planet->RotationSlowTimes == 0)
		SelfRotaion = 360 / (Planet->RotationHour / 24);
	else SelfRotaion = 360 / (Planet->RotationHour / 24) / Planet->RotationSlowTimes;

	TotalSelfTilt = Planet->RotationTilt;
	SelfTilt = (4 * TotalSelfTilt) / Planet->RevolutionDay;

	FRotator CurrentRotation = FRotator(Planet->RotationCurrentTilt, 0, 0);
	Planet->PlanetMesh->AddRelativeRotation(CurrentRotation);

	RelativeRevolution = 360 / Planet->RevolutionDay;

	CurrentRevolution = Planet->RevolutionCurrentDegree;

	bIsClockWise = Planet->IsTiltClockWise;
}


