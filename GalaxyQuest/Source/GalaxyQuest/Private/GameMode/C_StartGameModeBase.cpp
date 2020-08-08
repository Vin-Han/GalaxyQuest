// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/GameMode/C_StartGameModeBase.h"
#include "../Public/Widget/C_Start_UI.h"

#include "../Public/GameMode/C_Galaxy_Instance.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void AC_StartGameModeBase::StartPlay()
{
	Super::StartPlay();

	UGameplayStatics::GetPlayerController(this, 0)->bShowMouseCursor = true;

	targetSystemPath = "";

	StartUI = Cast<UC_Start_UI>(CreateWidget(GetGameInstance(), LoadClass<UC_Start_UI>
		(nullptr, TEXT("WidgetBlueprint'/Game/UI/Start/BP_Start_UI.BP_Start_UI_c'"))));
	if (StartUI)
	{
		StartUI->Btn_Into->OnClicked.AddDynamic(this, &AC_StartGameModeBase::OpenTargetLevel);
		StartUI->Btn_Quit->OnClicked.AddDynamic(this, &AC_StartGameModeBase::QuitCurGame);
		StartUI->AddToViewport();
	}

}

void AC_StartGameModeBase::QuitCurGame()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}

void AC_StartGameModeBase::OpenTargetLevel()
{
	if (targetSystemPath != "")
	{
		UGameplayStatics::OpenLevel(GetWorld(),*(targetSystemPath));
	}
	else
	{
		if (Cast<UC_Galaxy_Instance>(GetGameInstance())) 
		{
			Cast<UC_Galaxy_Instance>(GetGameInstance())->SendMessageToPlayer(FString("This map is not finished, wait for update !"));
		}
	}
}

void AC_StartGameModeBase::SetWidgetInfor(FString SystemPath, FString SystemName, FString SystemIntro)
{
	if (StartUI)
	{
		StartUI->Text_Name->SetText(FText::FromString(SystemName));
		StartUI->Text_Intro->SetText(FText::FromString(SystemIntro));
	}
	targetSystemPath = SystemPath;
}
