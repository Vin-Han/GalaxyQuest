// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/GameMode/C_Galaxy_Instance.h"

#include "../Public/SingleStar/Form/C_Source_List.h"
#include "../Public/Bag/C_BulletItemBase.h"
#include "../Public/Bag/C_ShieldItemBase.h"
#include "../Public/SingleStar/Beacon/C_Source_Item.h"
#include "../Public/Shield/C_Shield_Base.h"

#include "../Public/Widget/C_WarningInformation_UI.h"

void UC_Galaxy_Instance::OnStart()
{
	Super::OnStart();
	UE_LOG(LogTemp, Warning, TEXT("Game Start"));

	PlayerCurrentHp = -1;
	CurrentShield = 0;
	CurrentEqipedShield = nullptr;
	Money = -1;
	parentStarPath = "";
	UC_Source_List* tempList = UC_Source_List::GetList();
	tempList->UpdateBeaconList(SourceList);
	for (FSourceBase& tempItem : SourceList)
	{
		tempItem.totalCount = 0;
		tempItem.curCount = 0;
		tempItem.curPrice = 0;
		tempItem.singlePrice = 0;
		tempItem.instanceID = tempItem.targetItem->ID;
	}

	Infor_Widget = CreateWidget<UC_WarningInformation_UI>(this, LoadClass<UC_WarningInformation_UI>(nullptr,
		TEXT("WidgetBlueprint'/Game/UI/Start/BP_Warning_Information.BP_Warning_Information_c'")));
}

void UC_Galaxy_Instance::SendMessageToPlayer(FString message, float occorTime, FColor messageColor)
{
	if (Infor_Widget)
	{
		if (Infor_Widget->IsInViewport() == true)
		{
			Infor_Widget->RemoveFromViewport();
		}
		Infor_Widget->AddToViewport();
		Infor_Widget->SetWarningInformation(message, occorTime, messageColor);
	}
}
