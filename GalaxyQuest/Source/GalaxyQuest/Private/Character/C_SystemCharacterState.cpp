// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Character/C_SystemCharacterState.h"
#include "../Public/Bag/C_BulletItemBase.h"
#include "../Public/Bag/C_ShieldItemBase.h"

void AC_SystemCharacterState::AddItem(FBulletBagItem& newItem)
{
	for (FBulletBagItem tempItem : BulletList)
	{
		if (tempItem.BulletClass.GetDefaultObject()->BulletName 
			== newItem.BulletClass.GetDefaultObject()->BulletName)
		{
			tempItem.CurrentAccout += newItem.CurrentAccout;
			return;
		}
	}
	BulletList.Add(newItem);
}

void AC_SystemCharacterState::AddItem(FSheildBagItem& newItem)
{
	ShieldList.Add(newItem);
}