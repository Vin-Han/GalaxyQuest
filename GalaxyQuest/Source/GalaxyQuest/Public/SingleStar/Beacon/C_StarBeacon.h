// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_StarBeacon.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UWidgetComponent;
class UTextBlock;

UCLASS()
class GALAXYQUEST_API AC_StarBeacon : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_StarBeacon();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnyWhere, Category = "StaticMesh")
		UStaticMeshComponent* PointMesh;
	UPROPERTY(VisibleAnyWhere, Category = "CollisionCom")
		UBoxComponent* PointCollision;
	UPROPERTY(VisibleAnyWhere, Category = "WidgetCom")
		UWidgetComponent* PointWidget;

	UPROPERTY()
		UTextBlock* Text_Name;
	UPROPERTY()
		UTextBlock* Text_Information;

public:
	UPROPERTY(EditAnyWhere, Category = "PointInformation")
		FString Point_Name;
	UPROPERTY(EditAnyWhere, Category = "PointInformation")
		FString Point_Infor_S;

private:
	void InitializeShortWidget();
};
