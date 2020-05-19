// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "C_SystemCharacter.generated.h"

UCLASS()
class GALAXYQUEST_API AC_SystemCharacter : public APawn
{
	GENERATED_BODY()

public:
	AC_SystemCharacter();

	UPROPERTY(VisibleAnyWhere)
		class USpringArmComponent* SpringArmCom;
	UPROPERTY(VisibleAnyWhere)
		class UCameraComponent* CameraCom;
	UPROPERTY(VisibleAnyWhere)
		class USkeletalMeshComponent* ShipMesh;
	UPROPERTY(VisibleAnyWhere)
		class UBoxComponent* CollisionCom;
public:
	UPROPERTY(EditAnyWhere, Category = "Speed")
		float CameraSpeed;
	UPROPERTY(EditAnyWhere, Category = "Speed")
		float MoveSpeed;
	UPROPERTY(EditAnyWhere, Category = "Speed")
		float RotateSpeed;
	UPROPERTY(EditAnyWhere, Category = "Speed")
		float AttenuationSpeed;
	UPROPERTY(EditAnyWhere, Category = "Speed")
		float StopSpeed;
private:
	FVector CurrentSpeed;

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
		void MouseUpDown(float value);
	UFUNCTION()
		void MouseRightLeft(float value);
	UFUNCTION()
		void MoveForward(float value);
	UFUNCTION()
		void MoveTurn(float value);
	UFUNCTION()
		void MoveUpDown(float value);
	UFUNCTION()
		void UpdateCurrentSpeed(float value);

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
