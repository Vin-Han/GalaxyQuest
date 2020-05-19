#include "../Public/Character/C_SystemCharacterController.h"

#include "../Public/Character/C_SystemCharacter.h"
#include "../Public/Planet/C_NormalPlanetPawn.h"
#include "../Public/Widget/C_StarIntroduce_UI.h"

#include "Components/BoxComponent.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

#include "Kismet/GameplayStatics.h"

void AC_SystemCharacterController::BeginPlay(){
	Super::BeginPlay();
	InitializeShip();
	InitializeStar();
	TargetMapName = "/Game/Blueprint/BP_Map/BP_Test_Map";
}

void AC_SystemCharacterController::InitializeShip(){
	ShipCharacter = Cast<AC_SystemCharacter>(GetPawn());
	if (ShipCharacter){
		ShipCharacter->CollisionCom->OnComponentBeginOverlap.AddDynamic(this,&AC_SystemCharacterController::OverlapStar);
	}
}

void AC_SystemCharacterController::InitializeStar(){
	StarInfor = CreateWidget<UC_StarIntroduce_UI>(GetGameInstance(), 
				LoadClass<UC_StarIntroduce_UI>(nullptr, TEXT("WidgetBlueprint'/Game/UI/SolarSystemUI/BP_StarIntroduction.BP_StarIntroduction_c'")));
	if (StarInfor) {
		if (StarInfor->Button_Close) StarInfor->Button_Close->OnClicked.AddDynamic(this, &AC_SystemCharacterController::StarCloseBtnOnClicked);
		if (StarInfor->Button_Explore) StarInfor->Button_Explore->OnClicked.AddDynamic(this, &AC_SystemCharacterController::StarExploreBtnOnClicked);
	}
}

void AC_SystemCharacterController::OverlapStar(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool FromSweep, const FHitResult& HitRusult)
{
	AC_NormalPlanetPawn* tempStar = Cast<AC_NormalPlanetPawn>(OtherActor);
	if (tempStar) {
		if (StarInfor) {
			if (StarInfor->TextBlock_Name) StarInfor->TextBlock_Name->SetText(FText::FromString(tempStar->StarName));
			if (StarInfor->TextBlock_Intro)StarInfor->TextBlock_Intro->SetText(FText::FromString(tempStar->StarIntrodoce));;
			if (StarInfor->Image_Pic)	   StarInfor->Image_Pic->SetBrushFromTexture(tempStar->StarPicture);
			UGameplayStatics::SetGamePaused(this,true);
			bShowMouseCursor = true;
			StarInfor->AddToViewport();
		}
	}
}

void AC_SystemCharacterController::StarCloseBtnOnClicked(){
	UGameplayStatics::SetGamePaused(this, false);
	bShowMouseCursor = false;
	StarInfor->RemoveFromViewport();
}

void AC_SystemCharacterController::StarExploreBtnOnClicked(){
	UGameplayStatics::SetGamePaused(this, false);
	bShowMouseCursor = false;
	StarInfor->RemoveFromViewport();
	UE_LOG(LogTemp, Warning, TEXT("It is working"));
	UGameplayStatics::OpenLevel(GetWorld(), *TargetMapName);
}
