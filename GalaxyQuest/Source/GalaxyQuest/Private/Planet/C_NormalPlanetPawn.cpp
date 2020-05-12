
#include "../Public/Planet/C_NormalPlanetPawn.h"

#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Engine/Engine.h"

AC_NormalPlanetPawn::AC_NormalPlanetPawn()
{
	SceneCom		= CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	CollisionCom	= CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	PlanetMesh		= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlanetMeshComponent"));

	RootComponent = SceneCom;
	CollisionCom->SetupAttachment(SceneCom);
	PlanetMesh->SetupAttachment(CollisionCom);

}

void AC_NormalPlanetPawn::BeginPlay()
{
	Super::BeginPlay();

	RotationDay = 360 / ( RotationHour / 24 ) / 10;
	TiltDay = ( 4 * Tilt ) / RevolutionDay;
	RevolutionDay = 360 / RevolutionDay;

	FRotator CurRotation = FRotator(CurTilt,0,0);
	PlanetMesh->AddRelativeRotation(CurRotation);

	if (Target == NULL) {
		TargetPosition = FVector::ZeroVector;
		SetActorLocation(FVector::ZeroVector);
	}
	else { 
		TargetPosition = Target->GetActorLocation();
		SetActorLocation(Target->GetActorLocation());
	}
	SetActorRotation(FRotator(SunTilt, 0, 0));
}

void AC_NormalPlanetPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//control self rotation
	float PitchCheck = PlanetMesh->GetRelativeRotation().Pitch;
	if (PitchCheck < -Tilt) bIsTiltClockWise = true;
	else if (PitchCheck > Tilt)bIsTiltClockWise = false;
	FRotator TiltRotation = bIsTiltClockWise ? FRotator(TiltDay * DeltaTime, 0, 0):FRotator(-TiltDay * DeltaTime, 0, 0);
	PlanetMesh->AddRelativeRotation(TiltRotation);

	//
	FRotator SelfRotation = FRotator(0, RotationDay * DeltaTime,0);
	PlanetMesh->AddLocalRotation(SelfRotation);

	//control the position in the whole star system
	FVector Position = FVector(0, 0, GetActorLocation().Z);
	CurDegree += RevolutionDay * DeltaTime;
	if (CurDegree >= 360) CurDegree = 0;

	if (89.9 < CurDegree && CurDegree < 90.1)
		Position.Y = OvalB;
	else if (269.9 < CurDegree && CurDegree < 270.1)
		Position.Y = -OvalB;

	else if (90 < CurDegree && CurDegree < 270) {
		float temp = pow((OvalB2 + OvalA2 * pow(tan(CurDegree * 3.14 / 180.0), 2)), 0.5);
		Position.X = -((OvalA * OvalB) / temp);
		Position.Y = -((OvalA * OvalB / temp * tan(CurDegree * 3.14 / 180.0)));
	}
	else {
		float temp = pow((OvalB2 + OvalA2 * pow(tan(CurDegree * 3.14 / 180.0), 2)), 0.5);
		Position.X = (OvalA * OvalB) / temp;
		Position.Y = (OvalA * OvalB / temp * tan(CurDegree * 3.14 / 180.0));
	}
	CollisionCom->SetRelativeRotation(FRotator(0, CurDegree,0));
	CollisionCom->SetRelativeLocation(Position);
}