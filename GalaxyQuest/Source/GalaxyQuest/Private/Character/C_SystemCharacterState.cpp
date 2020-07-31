// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Character/C_SystemCharacterState.h"
#include "../Public/Bag/C_BulletItemBase.h"
#include "../Public/Bag/C_ShieldItemBase.h"

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

	FSourceBase creatItem;
	creatItem.totalCount = newItem->curCount;
	creatItem.targetItem = newItem->targetItem;
	SourceList.Add(creatItem);

	return true;
}

bool AC_SystemCharacterState::SubItem(FSourceBase* newItem)
{
	for (FSourceBase& tempSource : SourceList)
	{
		if (tempSource.targetItem->ID == newItem->targetItem->ID )
		{
			if (tempSource.totalCount >= newItem->curCount)
			{
				tempSource.totalCount -= newItem->curCount;
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}



