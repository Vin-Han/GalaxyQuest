#include "../Public/Planet/C_SubordinatePlanet.h"

#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

#include "../Public/Planet/C_NormalPlanetPawn.h"

#include "Engine/Engine.h"


AC_SubordinatePlanet::AC_SubordinatePlanet() 
{
	SceneCom = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	CollisionCom = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	PlanetMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlanetMesh"));

	RootComponent = SceneCom;
	CollisionCom->SetupAttachment(SceneCom);
	PlanetMesh->SetupAttachment(CollisionCom);

}

void AC_SubordinatePlanet::BeginPlay() 
{
	Super::BeginPlay();

	FVector Offset = FVector(RotationDistance, 0, 0);
	CollisionCom->AddRelativeLocation(Offset);
	if (RotationSlowTimes == 0)
	{
		RotationFrame = 360 / (RotationHour / 24);
	}
	else 
	{
		RotationFrame = 360 / (RotationHour / 24) / RotationSlowTimes;
	}

}

void AC_SubordinatePlanet::Tick(float DeltaSeconds) 
{
	Super::Tick(DeltaSeconds);

	FRotator SelfRotation = FRotator(0, RotationFrame, 0);
	AddActorLocalRotation(SelfRotation);
}

