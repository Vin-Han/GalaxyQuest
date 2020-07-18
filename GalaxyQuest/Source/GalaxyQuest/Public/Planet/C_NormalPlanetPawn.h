// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "../Public/Bag/C_BulletItemBase.h"
#include "../Public/Bag/C_ShieldItemBase.h"
#include "Engine/Texture2D.h"
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
	UPROPERTY(VisibleAnyWhere)
		USphereComponent* CollisionCom;

	UPROPERTY(VisibleAnyWhere)
		UStaticMeshComponent* PlanetMesh;

	UPROPERTY(VisibleAnyWhere)
		USceneComponent* SceneCom;

	UPROPERTY(VisibleAnyWhere)
		UStaticMeshComponent* OrbitMesh;

	UPROPERTY(VisibleAnyWhere)
		USphereComponent* BlockCom;

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
	
public:
	UPROPERTY(EditAnyWhere, CateGory = "Star_Infor")
		FString StarName;
	UPROPERTY(EditAnyWhere, CateGory = "Star_Infor")
		FString StarIntrodoce;
	UPROPERTY(EditAnyWhere, CateGory = "Star_Infor")
		FString StarMap;
	UPROPERTY(EditAnyWhere, CateGory = "Star_Infor")
		UTexture2D* StarPicture;

public:
	TArray<FBulletBagItem> BulletList;
	TArray<FSheildBagItem> ShieldList;

	bool bIfCanReflesh;
};
