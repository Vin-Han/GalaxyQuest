// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Texture2D.h"
#include "C_StarBeacon.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UWidgetComponent;
class UTextBlock;
struct FSourceBase;

UCLASS()
class GALAXYQUEST_API AC_StarBeacon : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_StarBeacon();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
#pragma region Base Structure
public:
	UPROPERTY(VisibleAnyWhere, Category = "StaticMesh")
		UStaticMeshComponent* PointMesh;
	UPROPERTY(VisibleAnyWhere, Category = "CollisionCom")
		UBoxComponent* PointCollision;
	UPROPERTY(VisibleAnyWhere, Category = "WidgetCom")
		UWidgetComponent* PointWidget;

private:
	void InitializeShortWidget();

#pragma endregion

#pragma region Base Information
public:
	UPROPERTY()
		UTextBlock* Text_Name;
	UPROPERTY()
		UTextBlock* Text_Information;

	UPROPERTY(EditAnyWhere, Category = "PointInformation")
		FString Point_Name;
	UPROPERTY(EditAnyWhere, Category = "PointInformation")
		FString Point_Infor_S;
	UPROPERTY(EditAnyWhere, Category = "PointInformation")
		FString Point_Infor_L;
	UPROPERTY(EditAnyWhere, Category = "PointInformation")
		UTexture2D* Point_Pic;

#pragma endregion

#pragma region Shop Item
private:
	void InitializeShopList();

public:
	UFUNCTION()
		void UpdateShopList();

public:
	UPROPERTY(EditAnyWhere, Category = "Shop")
		int UpdateTime;

	bool bIfCanUpdateNow;
	TArray<FSourceBase> ShopList;
	FTimerHandle TH_UpdateShop;
#pragma endregion


};
