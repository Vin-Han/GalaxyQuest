// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Widget/C_WarningInformation_UI.h"

#include "Components/TextBlock.h"

#include "TimerManager.h"

bool UC_WarningInformation_UI::Initialize() {
	if (!Super::Initialize())
	{
		return false;
	}
	Infor_Text = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Warning")));

	if (Infor_Text)
	{
		Infor_Text->SetVisibility(ESlateVisibility::Hidden);
	}
	return true;
}

void UC_WarningInformation_UI::SetWarningInformation(FString message, float occorTime, FColor messageColor)
{
	if (Infor_Text)
	{
		Infor_Text->SetColorAndOpacity(FSlateColor(FLinearColor(messageColor)));
		Infor_Text->SetText(FText::FromString(message));
		Infor_Text->SetVisibility(ESlateVisibility::SelfHitTestInvisible);

		GetWorld()->GetTimerManager().SetTimer(TH_Information, this, &UC_WarningInformation_UI::RemoveInformation, 1, false, occorTime);
	}
}

void UC_WarningInformation_UI::RemoveInformation()
{
	if (Infor_Text)
	{
		Infor_Text->SetVisibility(ESlateVisibility::Hidden);
	}
}
