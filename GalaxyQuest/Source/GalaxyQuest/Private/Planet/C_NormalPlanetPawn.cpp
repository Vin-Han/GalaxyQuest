
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
	BlockCom		= CreateDefaultSubobject<USphereComponent>(TEXT("BlockComponent"));

	RootComponent = SceneCom;
	CollisionCom->SetupAttachment(SceneCom);
	PlanetMesh->SetupAttachment(CollisionCom);
	OrbitMesh->SetupAttachment(SceneCom);
	BlockCom->SetupAttachment(SceneCom);
	
	StarMap = "";
	StarName = "NoNameNow";
	StarIntrodoce = "NoIntroduceNow";
	
}
