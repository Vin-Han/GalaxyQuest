// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_Shield_Base.generated.h"

UCLASS()
class GALAXYQUEST_API AC_Shield_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	AC_Shield_Base();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(VisibleAnyWhere)
		class UStaticMeshComponent* ShieldMesh;
public:
	UPROPERTY(EditAnyWhere, Category = "Attributes")
		float TotalShield;
	UPROPERTY(EditAnyWhere, Category = "Attributes")
		float Recovery;
	UPROPERTY(EditAnyWhere, Category = "Attributes")
		float RecoveryDelay;
public:
	FTimerHandle TH_BeginRecoveryShield;
	float CurrentShield;
private:
	bool bIsEqiped;
	bool bCanRecovery;
public:
	UFUNCTION()
		void BeginRecovery();
private:
	void SetRecoveryTH();

	void RecoveryShield(float DeltaTime);

public:
	FORCEINLINE float GetShieldPercent() { return CurrentShield / TotalShield;  }

	FORCEINLINE void SetShieldRecovery(bool IfCanRecovery) { bCanRecovery = IfCanRecovery; }

	FORCEINLINE void SetEqipState(bool IsEqiped) { bIsEqiped = IsEqiped; }

	FORCEINLINE void AfterTakeDamage() { 
		bCanRecovery = false;
		SetRecoveryTH(); }
};
