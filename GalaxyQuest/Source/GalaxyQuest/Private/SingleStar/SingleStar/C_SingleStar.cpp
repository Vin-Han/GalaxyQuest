// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/SingleStar/SingleStar/C_SingleStar.h"

#include "Components/StaticMeshComponent.h"

AC_SingleStar::AC_SingleStar()
{
	StarMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StarMesh"));
	RootComponent = StarMesh;

	RotationTime = 0.0f;
}

