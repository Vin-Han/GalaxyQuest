// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/GameMode/C_Galaxy_Instance.h"

#include "../Public/SingleStar/Form/C_Source_List.h"
#include "../Public/Bag/C_BulletItemBase.h"
#include "../Public/Bag/C_ShieldItemBase.h"
#include "../Public/SingleStar/Beacon/C_Source_Item.h"
#include "../Public/Shield/C_Shield_Base.h"

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
}
