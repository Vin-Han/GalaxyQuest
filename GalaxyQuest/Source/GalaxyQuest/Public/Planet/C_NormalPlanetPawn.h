// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "C_NormalPlanetPawn.generated.h"

class USphereComponent;
class USceneComponent;
class USplineComponent;
class AC_TrackPlanetPawn;

UCLASS()
class GALAXYQUEST_API AC_NormalPlanetPawn : public APawn
{
	GENERATED_BODY()

public:
	AC_NormalPlanetPawn();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
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

public:
	UPROPERTY(EditAnyWhere,CateGory = "Speed")
		float RotationHour;
	UPROPERTY(EditAnyWhere, CateGory = "Speed")
		float RevolutionDay;
	UPROPERTY(EditAnyWhere, CateGory = "Speed")
		float Tilt;
	UPROPERTY(EditAnyWhere, CateGory = "Speed")
		float CurTilt;
	UPROPERTY(EditAnyWhere, CateGory = "Speed")
		bool bIsTiltClockWise;

	UPROPERTY(EditAnyWhere, CateGory = "Revolution")
		AActor* Target;
	UPROPERTY(EditAnyWhere, CateGory = "Revolution")
		TSubclassOf<AC_TrackPlanetPawn> OrbitType;
	UPROPERTY(EditAnyWhere, CateGory = "Revolution")
		float CloseDistance;
	UPROPERTY(EditAnyWhere, CateGory = "Revolution")
		float FarDistance;
	UPROPERTY(EditAnyWhere, CateGory = "Revolution")
		float CurDegree;
	UPROPERTY(EditAnyWhere, CateGory = "Revolution")
		float SunTilt;

public:
	float RotationDay;
	float TiltDay;
	FVector TargetPosition;

	float OvalA;
	float OvalB;
	float OvalC;
	float OvalA2;
	float OvalB2;
};
