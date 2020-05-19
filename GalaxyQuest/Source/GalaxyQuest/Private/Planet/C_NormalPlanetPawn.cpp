
#include "../Public/Planet/C_NormalPlanetPawn.h"

#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Engine/Engine.h"

AC_NormalPlanetPawn::AC_NormalPlanetPawn()
{
	SceneCom		= CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	CollisionCom	= CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	PlanetMesh		= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlanetMesh"));
	OrbitMesh		= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OrbitMesh"));

	RootComponent = SceneCom;
	CollisionCom->SetupAttachment(SceneCom);
	PlanetMesh->SetupAttachment(CollisionCom);
	OrbitMesh->SetupAttachment(SceneCom);
	/*
	StarMap = "/Game/Blueprint/BP_Map/BP_SingleStar_Map.BP_SingleStar_Map'";
	StarName = "NoNameNow";
	StarIntrodoce = "NoIntroduceNow";
	*/
}
