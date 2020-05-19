// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_SubordinatePlanet.generated.h"

class USphereComponent;
class USceneComponent;
class AC_NormalPlanetPawn;

UCLASS()
class GALAXYQUEST_API AC_SubordinatePlanet : public AActor
{
	GENERATED_BODY()

public:

	AC_SubordinatePlanet();

	void BeginPlay() override;

	void Tick(float DeltaSeconds) override;

public:
	UPROPERTY(VisibleAnyWhere)
		USphereComponent* CollisionCom;

	UPROPERTY(VisibleAnyWhere)
		UStaticMeshComponent* PlanetMesh;

	UPROPERTY(VisibleAnyWhere)
		USceneComponent* SceneCom;

public:

	UPROPERTY()
		FVector TargetLoation;

	UPROPERTY(EditAnyWhere, CateGory = "AA_Self_Rotaion")
		float RotationSlowTimes;
	UPROPERTY(EditAnyWhere, CateGory = "AA_Self_Rotaion")
		float RotationDistance;
	UPROPERTY(EditAnyWhere, CateGory = "AA_Self_Rotaion")
		float RotationHour;
	float RotationFrame;
};
