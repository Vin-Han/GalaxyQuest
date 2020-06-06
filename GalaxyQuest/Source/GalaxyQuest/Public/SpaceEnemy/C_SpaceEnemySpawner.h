// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_SpaceEnemySpawner.generated.h"

UCLASS()
class GALAXYQUEST_API AC_SpaceEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_SpaceEnemySpawner();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnyWhere)
		class UBoxComponent* SpawnArea;

public:
	UPROPERTY(EditAnyWhere, Category = "Enemy")
		TSubclassOf<class AC_SpaceEnemy> Enemy;
	UPROPERTY(EditAnyWhere, Category = "Enemy")
		int EnemyMaxCount;
	UPROPERTY(EditAnyWhere, Category = "Enemy")
		float EnemyDistanceLimit;
	UPROPERTY(EditAnyWhere, Category = "Enemy")
		FString EnemyFrom;
public:
	bool SpawnEnemy();

	FTransform FindLocationInBox();

	bool ReduceCount();

	UFUNCTION()
		void ChildNumCheck();

public:
	int CurrentEnemy;

	class AC_SystemCharacter* PlayerShip;

};
