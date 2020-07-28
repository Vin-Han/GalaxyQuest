// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/SingleStar/Character/C_SingleStarPlayerController.h"
#include "../Public/SingleStar/Character/C_SingleStarPlayer.h"
#include "../Public/SingleStar/Beacon/C_StarBeacon.h"

#include "Components/StaticMeshComponent.h"
#include "Components/TextBlock.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

#include "DrawDebugHelpers.h"
#include "../Public/SingleStar/Form/C_Source_List.h"
#include "../Public/SingleStar/Form/C_Source_Form.h"

void AC_SingleStarPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ShipPlayer = Cast<AC_SingleStarPlayer>(GetPawn());
	bShowMouseCursor = true;

	AniRotationRocord[0] = 0.0f;
	AniRotationRocord[1] = 0.0f;

}

void AC_SingleStarPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	/*
	if (ShipPlayer)
	{
		
		ShipPlayer->ShipMesh->SetRelativeRotation(
		FRotator(ShipPlayer->ShipMesh->GetRelativeRotation().Pitch, 
			ShipPlayer->ShipMesh->GetRelativeRotation().Yaw + AniRotationRocord[0],
			ShipPlayer->ShipMesh->GetRelativeRotation().Roll + AniRotationRocord[1]));
	}
	*/
}

void AC_SingleStarPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UE_LOG(LogTemp, Warning, TEXT("BindAxis"));
	InputComponent->BindAxis("SingleUD", this, &AC_SingleStarPlayerController::SingleUD);
	InputComponent->BindAxis("SingleLR", this, &AC_SingleStarPlayerController::SingleLR);
	InputComponent->BindAxis("SingleFN", this, &AC_SingleStarPlayerController::SingleFN);

	InputComponent->BindAction("MouseTrackPoint", EInputEvent::IE_Pressed, this, &AC_SingleStarPlayerController::MouseTrackPoint);
}

/*
void AC_SingleStarPlayerController::ShowData()
{
	UC_Source_List* List = UC_Source_List::GetList();
	if (List)
	{
		TArray<FSourceData*> outItems;
		List->GetAllItem(outItems);
		if (outItems.Num() > 0)
		{
			for (FSourceData* temp : outItems)
			{
				UE_LOG(LogTemp, Warning, TEXT("Name : %s"), *temp->Name);
			}
			
		}
	}
}
*/

#pragma region Movement
void AC_SingleStarPlayerController::SingleUD(float value)
{
	if (ShipPlayer)
	{
		ShipPlayer->AddActorLocalRotation(FRotator(value, 0, 0));

		
		if ( (value < 0 && AniRotationRocord[0] > -SHIPMESH_RORATE_LIMIT) ||
			 (value > 0 && AniRotationRocord[0] < SHIPMESH_RORATE_LIMIT))
		{
			AniRotationRocord[0] += value;
		} 
		else if (value == 0 && AniRotationRocord[0] != 0)
		{
			AniRotationRocord[0] += AniRotationRocord[0] > 0 ? -1 : 1;
		}
	}
}

void AC_SingleStarPlayerController::SingleLR(float value)
{
	if (ShipPlayer)
	{
		ShipPlayer->AddActorWorldRotation(FRotator(0, value, 0));

		if ((value < 0 && AniRotationRocord[1] > -SHIPMESH_RORATE_LIMIT) ||
			(value > 0 && AniRotationRocord[1] < SHIPMESH_RORATE_LIMIT))
		{
			AniRotationRocord[1] += value;
		}
		else if (value == 0 && AniRotationRocord[1] != 0)
		{
			AniRotationRocord[1] += AniRotationRocord[1] > 0 ? -1 : 1;
		}
	}
}

void AC_SingleStarPlayerController::SingleFN(float value)
{
	if (ShipPlayer)
	{
		if (value > 0 && 
			ShipPlayer->ShipArm->TargetArmLength < ShipPlayer->maxArmSize)
		{
			ShipPlayer->ShipArm->TargetArmLength += value*20;
		}
		else if (value < 0 &&
			ShipPlayer->ShipArm->TargetArmLength > ShipPlayer->minArmSize)
		{
			ShipPlayer->ShipArm->TargetArmLength += value*20;
		}
	}
}

#pragma endregion

#pragma region Click Track
void AC_SingleStarPlayerController::MouseTrackPoint()
{
	FVector mouseLocation, mouseDirection;
	DeprojectMousePositionToWorld(mouseLocation,mouseDirection);
	FHitResult mouseHit;

	DrawDebugLine(GetWorld(), mouseLocation, mouseLocation + mouseDirection * SHIPTRADE_DISTANCE, FColor::Red, false, 5.0f);
	if ( GetWorld()->LineTraceSingleByChannel(
		mouseHit, mouseLocation, mouseLocation + mouseDirection * SHIPTRADE_DISTANCE, 
		ECollisionChannel::ECC_Visibility) )
	{

		AC_StarBeacon* tempBeacon = Cast<AC_StarBeacon> (mouseHit.GetActor());
		if (tempBeacon)
		{
			FString name = tempBeacon->Point_Name;
			UE_LOG(LogTemp, Warning, TEXT("%s"), *name);
		}
	}

}

#pragma endregion

