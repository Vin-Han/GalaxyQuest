// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "C_NormalPlanetPawn.generated.h"

class USphereComponent;
class USceneComponent;
class USplineComponent;
class USpringArmComponent;

UCLASS()
class GALAXYQUEST_API AC_NormalPlanetPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AC_NormalPlanetPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnyWhere)
		USphereComponent* CollisionCom;
	UPROPERTY(VisibleAnyWhere)
		UStaticMeshComponent* PlanetMesh;
	UPROPERTY(VisibleAnyWhere)
		USceneComponent* SceneCom;
public:
	UPROPERTY(EditAnyWhere,CateGory = "Speed")
		float SelfRotation;
	UPROPERTY(EditAnyWhere, CateGory = "Speed")
		float Revolution;
	UPROPERTY(EditAnyWhere, CateGory = "Speed")
		float CloseDis;
	UPROPERTY(EditAnyWhere, CateGory = "Speed")
		float FarDis;
	UPROPERTY(EditAnyWhere, CateGory = "Speed")
		float Tilt;
	UPROPERTY(EditAnyWhere, CateGory = "Speed")
		float CurDegree;

	UPROPERTY()
		float OvalA;
	UPROPERTY()
		float OvalB;
	UPROPERTY()
		float OvalC;
	UPROPERTY()
		float OvalA2;
	UPROPERTY()
		float OvalB2;
};
