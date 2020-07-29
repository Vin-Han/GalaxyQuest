// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/SingleStar/Character/C_SingleStarPlayerController.h"
#include "../Public/SingleStar/Character/C_Beacon_Player.h"
#include "../Public/SingleStar/Character/C_SingleStarPlayer.h"
#include "../Public/SingleStar/Beacon/C_Source_Item.h"

#include "../Public/Character/C_SystemCharacterState.h"

#include "../Public/SingleStar/Beacon/C_StarBeacon.h"
#include "../Public/SingleStar/Beacon/C_Beacon_Item.h"

#include "Components/StaticMeshComponent.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/ScrollBox.h"
#include "Components/Button.h"
#include "Components/Slider.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "DrawDebugHelpers.h"
#include "../Public/SingleStar/Form/C_Source_List.h"
#include "../Public/SingleStar/Form/C_Source_Form.h"

void AC_SingleStarPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ShipPlayer = Cast<AC_SingleStarPlayer>(GetPawn());
	if (ShipPlayer)
	{
		InitializeData();
		InitializeBeaconWidget();
		InitializeState();
	}
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

void AC_SingleStarPlayerController::InitializeData()
{
	bShowMouseCursor = true;

	AniRotationRocord[0] = 0.0f;
	AniRotationRocord[1] = 0.0f;
}

void AC_SingleStarPlayerController::InitializeState()
{
	ShipState = Cast<AC_SystemCharacterState>(this->PlayerState);
	//PlayerState = GetPlayerState<AC_SystemCharacterState>();
	if (ShipState)
	{
		UE_LOG(LogTemp, Warning, TEXT("Got PlayerState"));
	}
}

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
			LoadBeaconInfor(tempBeacon);
			LoadBeaconList(tempBeacon);
		}
	}

}

void AC_SingleStarPlayerController::LoadBeaconInfor(AC_StarBeacon* tempBeacon)
{
	if (BeaconWidget && BeaconWidget->IsInViewport() == false)
	{
		if (UGameplayStatics::IsGamePaused(GetWorld()) == false)
		{
			UGameplayStatics::SetGamePaused(GetWorld(), true);
		}
		BeaconWidget->Beacon_Name->SetText(FText::FromString(tempBeacon->Point_Name));
		BeaconWidget->Beacon_Intro->SetText(FText::FromString(tempBeacon->Point_Infor_S));


		if (ShipState)
		{
			BeaconWidget->Money_Text->SetText(FText::FromString(FString::FromInt(ShipState->Money)));
		}

		BeaconWidget->AddToViewport();
	}
}

void AC_SingleStarPlayerController::LoadBeaconList(AC_StarBeacon* tempBeacon)
{
	if (BeaconWidget)
	{
		BeaconWidget->Roll_Up->ClearChildren();
		for (FSourceBase& tempItem : tempBeacon->ShopList)
		{
			if (tempItem.totalCount != 0)
			{
				UC_Beacon_Item* newWidget = CreateWidget<UC_Beacon_Item>(GetGameInstance(),
					LoadClass<UC_Beacon_Item>(nullptr, TEXT("WidgetBlueprint'/Game/UI/SingleStar/BP_Beacon_Item.BP_Beacon_Item_c'")));
				newWidget->targetItem = &tempItem;

				newWidget->Text_Name->SetText(FText::FromString(tempItem.targetItem->Name));
				newWidget->Text_Count->SetText(FText::FromString(FString::FromInt(tempItem.totalCount)));
				newWidget->Text_Price->SetText(FText::FromString(FString::FromInt(tempItem.singlePrice)));
				newWidget->Bar_Buy->SetValue(0.0f);
				newWidget->UpdateSlider(0.0f);

				BeaconWidget->Roll_Up->AddChild(newWidget);
			}
		}
	}
}


#pragma endregion

#pragma region Beacon Widget
void AC_SingleStarPlayerController::InitializeBeaconWidget()
{
	
	BeaconWidget = CreateWidget<UC_Beacon_Player>(GetGameInstance(),
		LoadClass<UC_Beacon_Player>(nullptr,TEXT("WidgetBlueprint'/Game/UI/SingleStar/BP_Beacon_Player.BP_Beacon_Player_c'")));
	
}

#pragma endregion
