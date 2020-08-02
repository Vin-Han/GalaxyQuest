// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Character/C_SystemCharacterState.h"
#include "../Public/Bag/C_BulletItemBase.h"
#include "../Public/Bag/C_ShieldItemBase.h"

#include "../Public/GameMode/C_Galaxy_Instance.h"

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

bool AC_SystemCharacterState::LoadStateFromInstance()
{
	UC_Galaxy_Instance* tempInstance = Cast<UC_Galaxy_Instance>(GetGameInstance());
	if (tempInstance)
	{
		PlayerCurrentHp = tempInstance->PlayerCurrentHp;
		CurrentShield = tempInstance->CurrentShield;
		Money = tempInstance->Money;

		if (SourceList.Num() == 0)
		{
			for (FSourceBase& loadSource : tempInstance->SourceList)
			{
				SourceList.Add(loadSource);
			}	
			//UE_LOG(LogTemp, Warning, TEXT("FirstLoadSourceInstance,%d"), SourceList.Num());
		}
		else
		{
			int tempIndex = 0;
			for (FSourceBase& loadSource : tempInstance->SourceList)
			{
				if (SourceList.Num() > tempIndex)
				{
					SourceList[tempIndex].totalCount = loadSource.totalCount;
					tempIndex++;
				}
			}
			//UE_LOG(LogTemp, Warning, TEXT("SecondLoadSourceInstance,%d"), SourceList.Num());
		}

		for (FBulletBagItem& tempBullet : tempInstance->BulletList)
		{
			FBulletBagItem newBulletItem;
			newBulletItem.BulletClass = tempBullet.BulletClass;
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

bool AC_SystemCharacterState::StoreStateToInstance()
{
	UC_Galaxy_Instance* tempInstance = Cast<UC_Galaxy_Instance>(GetGameInstance());
	if (tempInstance)
	{
		tempInstance->PlayerCurrentHp = PlayerCurrentHp;
		tempInstance->CurrentShield = CurrentShield;
		tempInstance->Money = Money;

		int tempIndex = 0;
		for (FSourceBase& storeSource : SourceList)
		{
			if (tempInstance->SourceList.Num() > tempIndex)
			{
				tempInstance->SourceList[tempIndex].totalCount = storeSource.totalCount;
				tempIndex++;
			}
		}
		
		tempInstance->BulletList.RemoveAll([](FBulletBagItem& val) {return true; });
		for (FBulletBagItem& tempBullet : BulletList)
		{
			FBulletBagItem newBulletItem;
			newBulletItem.BulletClass = tempBullet.BulletClass;
			newBulletItem.TotalAccout = tempBullet.TotalAccout;
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



