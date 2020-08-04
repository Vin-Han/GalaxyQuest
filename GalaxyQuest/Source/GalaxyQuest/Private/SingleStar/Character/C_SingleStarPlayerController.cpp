// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/SingleStar/Character/C_SingleStarPlayerController.h"
#include "../Public/SingleStar/Character/C_Beacon_Player.h"
#include "../Public/SingleStar/Character/C_SingleStarPlayer.h"
#include "../Public/SingleStar/Character/C_Single_Bag.h"

#include "../Public/SingleStar/Beacon/C_Source_Item.h"
#include "../Public/SingleStar/Character/C_Bag_Item_Simple.h"

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
		InitializeBagWidget();
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
	InputComponent->BindAxis("SingleUD", this, &AC_SingleStarPlayerController::SingleUD);
	InputComponent->BindAxis("SingleLR", this, &AC_SingleStarPlayerController::SingleLR);
	InputComponent->BindAxis("SingleFN", this, &AC_SingleStarPlayerController::SingleFN);
	
	InputComponent->BindAction("MouseTrackPoint", EInputEvent::IE_Pressed, this, &AC_SingleStarPlayerController::MouseTrackPoint);
	InputComponent->BindAction("SingleOpenBag", EInputEvent::IE_Pressed, this, &AC_SingleStarPlayerController::OpenBag);
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
	if (ShipState)
	{
		ShipState->LoadStateFromInstance();
		if (ShipState->PlayerCurrentHp == -1)
		{
			ShipState->PlayerCurrentHp = 1;
		}
		if (ShipState->Money == -1)
		{
			ShipState->Money = 999;
		}
		//InitializeItemList();
	}
}

void AC_SingleStarPlayerController::InitializeBagWidget()
{
	bagWidget = CreateWidget<UC_Single_Bag>(GetGameInstance(),
		LoadClass<UC_Single_Bag>(nullptr, TEXT("WidgetBlueprint'/Game/UI/SingleStar/BP_Bag_SingleStar.BP_Bag_SingleStar_c'")));
	if (bagWidget)
	{
		bagWidget->Btn_Close->OnClicked.AddDynamic(this,&AC_SingleStarPlayerController::CloseBag);
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
			tempStarPoint = tempBeacon;
			tempStarPoint->bIfCanUpdateNow = false;
			LoadBeaconInfor(tempBeacon);
			LoadBeaconList(tempBeacon);
			LoadBagList(tempBeacon);
		}
	}

}

void AC_SingleStarPlayerController::ClosePoint()
{
	if (BeaconWidget)
	{
		BeaconWidget->Roll_Up->ClearChildren();
		BeaconWidget->Roll_Down->ClearChildren();
		BeaconWidget->CloseShop();
		if (BeaconWidget->IsInViewport() == true)
		{
			BeaconWidget->RemoveFromViewport();
		}
	}
	if (tempStarPoint)
	{
		tempStarPoint->bIfCanUpdateNow = true;
		tempStarPoint = nullptr;
	}
	if (UGameplayStatics::IsGamePaused(GetWorld()) == true)
	{
		UGameplayStatics::SetGamePaused(GetWorld(), false);
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
				newWidget->playerController = this;

				newWidget->Text_Name->SetText(FText::FromString(tempItem.targetItem->Name));
				newWidget->Text_Count->SetText(FText::FromString(FString::FromInt(tempItem.totalCount)));
				newWidget->Text_Price->SetText(FText::FromString(FString::FromInt(tempItem.singlePrice)));

				newWidget->Text_CurCount->SetText(FText::FromString("Buy Count :"));
				newWidget->Text_CurPrice->SetText(FText::FromString("Buy Price :"));
				newWidget->Text_Buy->SetText(FText::FromString("Buy"));

				newWidget->Bar_Buy->SetValue(0.0f);
				newWidget->UpdateSlider(0.0f);

				newWidget->Btn_Buy->OnClicked.AddDynamic(newWidget,&UC_Beacon_Item::BuyItems);

				BeaconWidget->Roll_Up->AddChild(newWidget);
			}
		}
	}
}

void AC_SingleStarPlayerController::LoadBagList(AC_StarBeacon* tempBeacon)
{
	if (BeaconWidget && ShipState)
	{
		BeaconWidget->Roll_Down->ClearChildren();
		int tempIndex = 0;
		//UE_LOG(LogTemp, Warning, TEXT("LoadingSourceList,%d"), ShipState->SourceList.Num());
		for (FSourceBase& tempItem : ShipState->SourceList)
		{
			if (tempItem.totalCount != 0)
			{

				UC_Beacon_Item* newWidget = CreateWidget<UC_Beacon_Item>(GetGameInstance(),
					LoadClass<UC_Beacon_Item>(nullptr, TEXT("WidgetBlueprint'/Game/UI/SingleStar/BP_Beacon_Item.BP_Beacon_Item_c'")));
				newWidget->targetItem = &tempItem;
				newWidget->playerController = this;

				if (tempStarPoint && tempIndex < tempStarPoint->ShopList.Num())
				{
					tempItem.singlePrice = tempStarPoint->ShopList[tempIndex].singlePrice;
					tempIndex++;
				}

				newWidget->Text_Name->SetText(FText::FromString(tempItem.targetItem->Name));
				newWidget->Text_Count->SetText(FText::FromString(FString::FromInt(tempItem.totalCount)));
				newWidget->Text_Price->SetText(FText::FromString(FString::FromInt(tempItem.singlePrice)));

				newWidget->Text_CurCount->SetText(FText::FromString("Sell Count :"));
				newWidget->Text_CurPrice->SetText(FText::FromString("Sell Price :"));
				newWidget->Text_Buy->SetText(FText::FromString("Sell"));

				newWidget->Bar_Buy->SetValue(0.0f);
				newWidget->UpdateSlider(0.0f);

				newWidget->Btn_Buy->OnClicked.AddDynamic(newWidget, &UC_Beacon_Item::SellItems);

				BeaconWidget->Roll_Down->AddChild(newWidget);
			}
		}
	}
}

bool AC_SingleStarPlayerController::BuySource(FSourceBase* newItem)
{
	if (ShipState && 
		ShipState->Money >= newItem->curPrice && 
		ShipState->AddItem(newItem))
	{
		ShipState->Money -= newItem->curPrice;
		BeaconWidget->Money_Text->SetText(FText::FromString(FString::FromInt(ShipState->Money)));
		if (tempStarPoint)
		{
			LoadBagList(tempStarPoint);
		}
		return true;
	}
	return false;
}

bool AC_SingleStarPlayerController::SellSource(FSourceBase* newItem)
{
	if (ShipState && newItem &&
		ShipState->SubItem(newItem) ) 
	{
		ShipState->Money += newItem->curPrice;
		BeaconWidget->Money_Text->SetText(FText::FromString(FString::FromInt(ShipState->Money)));
		if (tempStarPoint)
		{
			LoadBagList(tempStarPoint);
		}
		return true;
	}
	return false;
}

#pragma endregion

#pragma region Beacon Widget
void AC_SingleStarPlayerController::InitializeBeaconWidget()
{
	
	BeaconWidget = CreateWidget<UC_Beacon_Player>(GetGameInstance(),
		LoadClass<UC_Beacon_Player>(nullptr,TEXT("WidgetBlueprint'/Game/UI/SingleStar/BP_Beacon_Player.BP_Beacon_Player_c'")));
	if (BeaconWidget)
	{
		BeaconWidget->ClosePage_Btn->OnClicked.AddDynamic(this,&AC_SingleStarPlayerController::ClosePoint);
	}
}

void AC_SingleStarPlayerController::InitializeItemList()
{
	UC_Source_List* tempList = UC_Source_List::GetList();
	if (ShipState)
	{
		tempList->UpdateBeaconList(ShipState->SourceList);
		for (FSourceBase& tempSource : ShipState->SourceList)
		{
			tempSource.totalCount = 0;
			tempSource.singlePrice = 0;
		}
	}
}

#pragma endregion

#pragma region Player Bag
void AC_SingleStarPlayerController::OpenBag()
{
	if (BeaconWidget && BeaconWidget->IsInViewport() == false &&
		bagWidget && bagWidget->IsInViewport() == false)
	{
		if (UGameplayStatics::IsGamePaused(this) == false)
		{
			UGameplayStatics::SetGamePaused(this, true);
		}
		LoadBagList();
		bagWidget->AddToViewport();
	}
}

void AC_SingleStarPlayerController::CloseBag()
{
	if (bagWidget && bagWidget->IsInViewport() == true)
	{
		if (UGameplayStatics::IsGamePaused(this) == true)
		{
			UGameplayStatics::SetGamePaused(this, false);
		}
		bagWidget->List_Roll->ClearChildren();
		bagWidget->RemoveFromViewport();
	}
}

void AC_SingleStarPlayerController::BackToSystem()
{
}

void AC_SingleStarPlayerController::LoadBagList()
{
	if (bagWidget)
	{
		bagWidget->List_Roll->ClearChildren();

		if (ShipState)
		{
			for (FSourceBase& tempItem : ShipState->SourceList)
			{
				if (tempItem.totalCount > 0)
				{
					UC_Bag_Item_Simple* newWidget = CreateWidget<UC_Bag_Item_Simple>(GetGameInstance(),
						LoadClass<UC_Bag_Item_Simple>(nullptr, TEXT("WidgetBlueprint'/Game/UI/SingleStar/BP_Bag_Item_Simple.BP_Bag_Item_Simple_c'")));
					newWidget->Item_Name->SetText(FText::FromString(tempItem.targetItem->Name));
					newWidget->Item_Count->SetText(FText::FromString(FString::FromInt(tempItem.totalCount)));
					bagWidget->List_Roll->AddChild(newWidget);
				}
			}

		}
	}
}


#pragma endregion
