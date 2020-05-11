// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Planet/C_NormalPlanetPawn.h"

#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SplineComponent.h"



// Sets default values
AC_NormalPlanetPawn::AC_NormalPlanetPawn()
{
	SceneCom		= CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	CollisionCom	= CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	PlanetMesh		= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlanetMeshComponent"));
	SplineCom		= CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	RootComponent = SceneCom;
	CollisionCom->SetupAttachment(SceneCom);
	PlanetMesh->SetupAttachment(SceneCom);
	SplineCom->SetupAttachment(SceneCom);

	SplineCom->SetClosedLoop(true);
}

// Called when the game starts or when spawned
void AC_NormalPlanetPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

