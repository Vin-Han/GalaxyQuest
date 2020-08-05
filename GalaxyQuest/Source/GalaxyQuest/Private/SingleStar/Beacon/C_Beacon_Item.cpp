// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/SingleStar/Beacon/C_Beacon_Item.h"
#include "../Public/SingleStar/Beacon/C_Source_Item.h"
#include "../Public/SingleStar/Character/C_SingleStarPlayerController.h"

#include "Components/TextBlock.h"
#include "Components/Slider.h"
#include "Components/Button.h"


bool UC_Beacon_Item::Initialize() {
	if (!Super::Initialize())
	{
		return false;
	}

	Btn_Buy = Cast<UButton>(GetWidgetFromName(TEXT("Button_Buy")));

	Text_Buy = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Buy")));

	Text_Name = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Name")));

	Text_Price = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Price")));

	Text_Count = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Count")));

	Text_BuyCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_BuyCount")));

	Text_BuyPrice = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_BuyPrice")));

	Text_CurCount = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_BuyCount_Const")));

	Text_CurPrice = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_BuyPrice_Const")));

	Bar_Buy = Cast<USlider>(GetWidgetFromName(TEXT("Slider_Buy")));

	Bar_Buy->OnValueChanged.AddDynamic(this,&UC_Beacon_Item::UpdateSlider);

	return true;
}

void UC_Beacon_Item::UpdateSlider(float value)
{
	if (targetItem)
	{
		targetItem->curCount = targetItem->totalCount * value;
		targetItem->curPrice = targetItem->singlePrice * targetItem->curCount;
		Text_BuyCount->SetText(FText::FromString(FString::FromInt(targetItem->curCount)));
		Text_BuyPrice->SetText(FText::FromString(FString::FromInt(targetItem->curPrice)));
	}
}

void UC_Beacon_Item::BuyItems()
{
	if (targetItem && playerController)
	{
		AC_SingleStarPlayerController* tempCon = Cast<AC_SingleStarPlayerController>(playerController);
		if (tempCon && tempCon->BuySource(targetItem))
		{
			targetItem->totalCount -= targetItem->curCount;
			Text_Count->SetText(FText::FromString(FString::FromInt(targetItem->totalCount)));
			UpdateSlider(0.0f);
			Bar_Buy->SetValue(0.0f);
		}
	}
}

void UC_Beacon_Item::SellItems()
{
	if (targetItem && playerController)
	{
		AC_SingleStarPlayerController* tempCon = Cast<AC_SingleStarPlayerController>(playerController);
		if (tempCon && tempCon->SellSource(targetItem))
		{
			//targetItem->totalCount -= targetItem->curCount;
			Text_Count->SetText(FText::FromString(FString::FromInt(targetItem->totalCount)));
			UpdateSlider(0.0f);
			Bar_Buy->SetValue(0.0f);
		}
	}
}
