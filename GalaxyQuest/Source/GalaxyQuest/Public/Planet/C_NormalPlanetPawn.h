// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "C_NormalPlanetPawn.generated.h"

class USphereComponent;
class USceneComponent;

UCLASS()
class GALAXYQUEST_API AC_NormalPlanetPawn : public APawn
{
	GENERATED_BODY()

public:
	AC_NormalPlanetPawn();
public:
	/*
	CollisionCom is for gameplay
	SceneCom is for the changeable tilt of itself
	PlanetMesh is for self rotation
	*/
	UPROPERTY(VisibleAnyWhere)
		USphereComponent* CollisionCom;

	UPROPERTY(VisibleAnyWhere)
		UStaticMeshComponent* PlanetMesh;

	UPROPERTY(VisibleAnyWhere)
		USceneComponent* SceneCom;

	UPROPERTY(VisibleAnyWhere)
		UStaticMeshComponent* OrbitMesh;

public:
	/*Self Rotation*/
	UPROPERTY(EditAnyWhere, CateGory = "AA_Self_Rotaion")
		float RotationHour;
	UPROPERTY(EditAnyWhere, CateGory = "AA_Self_Rotaion")
		float RotationTilt;
	UPROPERTY(EditAnyWhere, CateGory = "AA_Self_Rotaion")
		float RotationCurrentTilt;
	UPROPERTY(EditAnyWhere, CateGory = "AA_Self_Rotaion")
		float RotationSlowTimes;
	UPROPERTY(EditAnyWhere, CateGory = "AA_Self_Rotaion")
		bool  IsTiltClockWise;

	/*Relative Revolution*/
	UPROPERTY(EditAnyWhere, CateGory = "AB_Relative_Recolution")
		AC_NormalPlanetPawn* RevolutionTarget;
	UPROPERTY(EditAnyWhere, CateGory = "AB_Relative_Recolution")
		float RevolutionDay;
	UPROPERTY(EditAnyWhere, CateGory = "AB_Relative_Recolution")
		float CloseDistance;
	UPROPERTY(EditAnyWhere, CateGory = "AB_Relative_Recolution")
		float FarDistance;
	UPROPERTY(EditAnyWhere, CateGory = "AB_Relative_Recolution")
		float RevolutionTilt;
	UPROPERTY(EditAnyWhere, CateGory = "AB_Relative_Recolution")
		float RevolutionCurrentDegree;

};
