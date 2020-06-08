// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Widget/C_EnemyBlood_UI.h"

#include "Components/ProgressBar.h"

bool UC_EnemyBlood_UI::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}
	Bar_Blood = Cast<UProgressBar>(GetWidgetFromName(TEXT("Bar_EnemyBlood")));
	return true;
}