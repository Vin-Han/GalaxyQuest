// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Character/C_SystemCharacter.h"

// Sets default values
AC_SystemCharacter::AC_SystemCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_SystemCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_SystemCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AC_SystemCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

