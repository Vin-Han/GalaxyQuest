// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Widget/C_Galaxy_Point.h"

#include "../Public/GameMode/C_StartGameModeBase.h"

#include "Components/Button.h"

#include "Kismet/GameplayStatics.h"

bool UC_Galaxy_Point::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	Btn_Point = Cast<UButton>(GetWidgetFromName(TEXT("Button_PointInfor")));

	if (Btn_Point)
	{
		Btn_Point->OnClicked.AddDynamic(this,&UC_Galaxy_Point::SetGameModeInfor);
	}


	return true;
}

void UC_Galaxy_Point::SetGameModeInfor()
{
	AC_StartGameModeBase* tempGameMode = Cast<AC_StartGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (tempGameMode)
	{
		tempGameMode->SetWidgetInfor(SystemPath, SystemPath, SystemIntro);
	}
}
