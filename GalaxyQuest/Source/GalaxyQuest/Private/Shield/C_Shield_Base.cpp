// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Shield/C_Shield_Base.h"

#include "Components/StaticMeshComponent.h"

#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values
AC_Shield_Base::AC_Shield_Base()
{
	PrimaryActorTick.bCanEverTick = true;
	ShieldMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShieldMesh"));
	//ShieldMesh->SetupAttachment(RootComponent);
	RootComponent = ShieldMesh;
	ShieldMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	TotalShield = 200;
	CurrentShield = 0;
	Recovery = 10;
	RecoveryDelay = 3;
	bIsEqiped = false;
	bCanRecovery = true;

	ShieldName = "BaseShield";
}

void AC_Shield_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

void AC_Shield_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RecoveryShield(DeltaTime);
	if (CurrentShield < 1)
	{
		ShieldMesh->SetVisibility(false);
	}
	else
	{
		ShieldMesh->SetVisibility(true);
	}
}

void AC_Shield_Base::SetRecoveryTH()
{
	GetWorld()->GetTimerManager().SetTimer(
		TH_BeginRecoveryShield,this, &AC_Shield_Base::BeginRecovery, 1, false, RecoveryDelay);
}

void AC_Shield_Base::RecoveryShield(float DeltaTime)
{
	if (bCanRecovery && CurrentShield < TotalShield)
	{
		CurrentShield += Recovery * DeltaTime;
		if (CurrentShield >= TotalShield)
		{
			CurrentShield = TotalShield;
		}
	}
}

void AC_Shield_Base::BeginRecovery()
{
	if (bIsEqiped)
	{
		bCanRecovery = true;
	}
}

