// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Character/C_SystemCharacterState.h"
#include "../Public/Bag/C_BulletItemBase.h"
#include "../Public/Bag/C_ShieldItemBase.h"

#include "../Public/GameMode/C_Galaxy_Instance.h"
#include "../Public/SingleStar/Form/C_Source_List.h"

#include "../Public/SingleStar/Form/C_Source_Form.h"

#include "Kismet/GameplayStatics.h"
bool AC_SystemCharacterState::AddItem(FBulletBagItem* newItem)
{
	for (FBulletBagItem& tempItem : BulletList)
	{
		if (tempItem.BulletClass.GetDefaultObject()->BulletName 
			== newItem->BulletClass.GetDefaultObject()->BulletName)
		{
			tempItem.CurrentAccout += newItem->CurrentAccout;
			return true;
		}
	}

	FBulletBagItem creatItem;
	creatItem.BulletClass = newItem->BulletClass;
	creatItem.CurrentAccout = newItem->CurrentAccout;
	creatItem.TotalAccout = newItem->CurrentAccout;
	creatItem.CurrentLoadingTime = 0;

	BulletList.Add(creatItem);
	return true;
}

bool AC_SystemCharacterState::AddItem(FSheildBagItem* newItem)
{
	for (FSheildBagItem& tempItem : ShieldList)
	{
		if (tempItem.ShieldClass.GetDefaultObject()->ShieldName
			== newItem->ShieldClass.GetDefaultObject()->ShieldName)
		{
			return false;
		}
	}
	FSheildBagItem creatItem;
	creatItem.ShieldClass = newItem->ShieldClass;
	creatItem.bIsInEquiped = false;
	ShieldList.Add(creatItem);
	return true;
}

bool AC_SystemCharacterState::AddItem(FSourceBase* newItem)
{
	for (FSourceBase& tempSource : SourceList)
	{
		if (tempSource.targetItem->ID == 
			newItem->targetItem->ID)
		{
			tempSource.totalCount += newItem->curCount;
			return true;
		}
	}
	return false;
}

bool AC_SystemCharacterState::SubItem(FSourceBase* newItem)
{
	for (FSourceBase& tempSource : SourceList)
	{
		if (tempSource.targetItem->ID == newItem->targetItem->ID && 
			tempSource.totalCount >= newItem->curCount)
		{
			tempSource.totalCount -= newItem->curCount;
			return true;
		}
	}
	return false;
}

bool AC_SystemCharacterState::LoadStateFromInstance()
{
	UE_LOG(LogTemp, Warning, TEXT("Loading Data"));
	UC_Galaxy_Instance* tempInstance = Cast<UC_Galaxy_Instance>(GetGameInstance());
	if (tempInstance)
	{
		PlayerCurrentHp = tempInstance->PlayerCurrentHp;
		CurrentShield = tempInstance->CurrentShield;
		Money = tempInstance->Money;

		SourceList.RemoveAll([](FSourceBase& val) {return true; });

		UC_Source_List::GetList()->UpdateBeaconList(SourceList);
		int tempIndex = 0;
		for (FSourceBase& tempItem : SourceList)
		{
			if (tempIndex < tempInstance->SourceList.Num() && 
				tempItem.targetItem->ID == tempInstance->SourceList[tempIndex].instanceID)
			{
				tempItem.totalCount = tempInstance->SourceList[tempIndex].totalCount;
				tempItem.curCount = tempInstance->SourceList[tempIndex].curCount;
				tempItem.curPrice = tempInstance->SourceList[tempIndex].curPrice;
				tempItem.singlePrice = tempInstance->SourceList[tempIndex].singlePrice;
				tempIndex++;
			}
		}
		UE_LOG(LogTemp, Warning, TEXT("SourceNum,%d"), SourceList.Num());

		for (FBulletBagItem& tempBullet : tempInstance->BulletList)
		{
			FBulletBagItem newBulletItem;
			newBulletItem.BulletClass = tempBullet.BulletClass;
			newBulletItem.CurrentAccout = tempBullet.CurrentAccout;
			newBulletItem.TotalAccout = tempBullet.TotalAccout;
			newBulletItem.CurrentLoadingTime = tempBullet.CurrentLoadingTime;
			BulletList.Add(newBulletItem);
		}

		for (FSheildBagItem& tempBullet : tempInstance->ShieldList)
		{
			FSheildBagItem newBulletItem;
			newBulletItem.ShieldClass = tempBullet.ShieldClass;
			newBulletItem.bIsInEquiped = tempBullet.bIsInEquiped;
			ShieldList.Add(newBulletItem);
		}
		//UE_LOG(LogTemp, Warning, TEXT("LoadShield,%d"), ShieldList.Num());

		return true;
	}
	return false;
}

bool AC_SystemCharacterState::StoreStateToInstance(bool bIfStoreStarPath)
{
	UE_LOG(LogTemp, Warning, TEXT("Storing Data"));
	UC_Galaxy_Instance* tempInstance = Cast<UC_Galaxy_Instance>(GetGameInstance());
	if (tempInstance)
	{
		tempInstance->PlayerCurrentHp = PlayerCurrentHp;
		tempInstance->CurrentShield = CurrentShield;
		tempInstance->Money = Money;
		if (bIfStoreStarPath)
		{
			tempInstance->parentStarPath = UGameplayStatics::GetCurrentLevelName(this);
		}
		int tempIndex = 0;

		tempInstance->SourceList.RemoveAll([](FSourceBase& val) {return true; });
		for (FSourceBase& storeSource : SourceList)
		{
			FSourceBase newSource;
			newSource.curCount = storeSource.curCount;
			newSource.curPrice = storeSource.curPrice;
			newSource.singlePrice = storeSource.singlePrice;
			newSource.instanceID = storeSource.targetItem->ID;
			newSource.totalCount = storeSource.totalCount;
			tempInstance->SourceList.Add(newSource);
		}
		
		tempInstance->BulletList.RemoveAll([](FBulletBagItem& val) {return true; });
		for (FBulletBagItem& tempBullet : BulletList)
		{
			FBulletBagItem newBulletItem;
			newBulletItem.BulletClass = tempBullet.BulletClass;
			newBulletItem.TotalAccout = tempBullet.TotalAccout;
			newBulletItem.CurrentAccout = tempBullet.CurrentAccout;
			newBulletItem.CurrentLoadingTime = tempBullet.CurrentLoadingTime;
			tempInstance->BulletList.Add(newBulletItem);
		}

		tempInstance->ShieldList.RemoveAll([](FSheildBagItem& val) {return true; });
		for (FSheildBagItem& tempBullet : ShieldList)
		{
			FSheildBagItem newBulletItem;
			newBulletItem.ShieldClass = tempBullet.ShieldClass;
			newBulletItem.bIsInEquiped = tempBullet.bIsInEquiped;
			tempInstance->ShieldList.Add(newBulletItem);
		}
		//UE_LOG(LogTemp, Warning, TEXT("StoreShield,%d"), tempInstance->ShieldList.Num());

		return true;
	}
	return false;
}



