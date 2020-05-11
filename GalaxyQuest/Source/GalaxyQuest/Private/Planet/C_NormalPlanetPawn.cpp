// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Planet/C_NormalPlanetPawn.h"

#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AC_NormalPlanetPawn::AC_NormalPlanetPawn()
{
	SceneCom		= CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	CollisionCom	= CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	PlanetMesh		= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlanetMeshComponent"));

	RootComponent = SceneCom;
	CollisionCom->SetupAttachment(SceneCom);
	PlanetMesh->SetupAttachment(CollisionCom);

}

// Called when the game starts or when spawned
void AC_NormalPlanetPawn::BeginPlay()
{
	Super::BeginPlay();

	FRotator TiltRotate = FRotator(Tilt, 0, 0);
	AddActorWorldRotation(TiltRotate);

	OvalA = (CloseDis + FarDis) / 2;
	OvalC = (FarDis - CloseDis) / 2;

	OvalA2 = OvalA * OvalA;
	OvalB2 = OvalA2 - (OvalC * OvalC);

	OvalB = pow(OvalB2, 0.5);
}

