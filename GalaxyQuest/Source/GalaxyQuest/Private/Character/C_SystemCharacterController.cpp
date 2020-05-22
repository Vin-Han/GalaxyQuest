#include "../Public/Character/C_SystemCharacterController.h"

#include "../Public/Character/C_SystemCharacter.h"
#include "../Public/Planet/C_NormalPlanetPawn.h"
#include "../Public/Widget/C_StarIntroduce_UI.h"
#include "../Public/Widget/C_SolarUserFace.h"
#include "../Public/GameMode/C_SolarSystemGameMode.h"

#include "Components/BoxComponent.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

void AC_SystemCharacterController::BeginPlay(){
	Super::BeginPlay();
	CleanupGameViewport();
	InitializeShip();
	InitializeStarWidget();
	InitializeShipWidget();
	InitializeDistanceLimit();
	TargetMapName = "/Game/Blueprint/BP_Map/BP_Test_Map";
	ArmChangeRate = 120;
	CameraChangeRate = 20;

	SpeedUptime = 4;
	CurSpeedUpTime = SpeedUptime;

}


void AC_SystemCharacterController::InitializeShip(){
	ShipCharacter = Cast<AC_SystemCharacter>(GetPawn());
	if (ShipCharacter){
		ShipCharacter->CollisionCom->OnComponentBeginOverlap.AddDynamic(this,&AC_SystemCharacterController::OverlapStar);
	}
}

void AC_SystemCharacterController::InitializeStarWidget(){
	StarInfor = CreateWidget<UC_StarIntroduce_UI>(GetGameInstance(), 
				LoadClass<UC_StarIntroduce_UI>(nullptr, TEXT("WidgetBlueprint'/Game/UI/SolarSystemUI/BP_StarIntroduction.BP_StarIntroduction_c'")));
	if (StarInfor) {
		if (StarInfor->Button_Close) StarInfor->Button_Close->OnClicked.AddDynamic(this, &AC_SystemCharacterController::StarCloseBtnOnClicked);
		if (StarInfor->Button_Explore) StarInfor->Button_Explore->OnClicked.AddDynamic(this, &AC_SystemCharacterController::StarExploreBtnOnClicked);
	}
}

void AC_SystemCharacterController::InitializeShipWidget()
{
	ShipUI = CreateWidget<UC_SolarUserFace>(GetGameInstance(),
											LoadClass<UC_SolarUserFace>(nullptr, TEXT("WidgetBlueprint'/Game/UI/SolarSystemUI/BP_SolarUserFace.BP_SolarUserFace_c'")));
	if (ShipUI){
		ShipUI->AddToViewport();
		if (ShipUI->Bar_Speed)ShipUI->Bar_Speed->SetPercent(1.f);
		if (ShipUI->Bar_Vertical)ShipUI->Bar_Vertical->SetPercent(1.f);
		if (ShipUI->Bar_Horizontal)ShipUI->Bar_Horizontal->SetPercent(1.f);
	}
}

void AC_SystemCharacterController::InitializeDistanceLimit(){
	AC_SolarSystemGameMode* GameMode = Cast<AC_SolarSystemGameMode>(UGameplayStatics::GetGameMode(this));
	if (GameMode){
		VerDisLim = GameMode->RadiusLimit;
		HorDisLim = GameMode->HeightLimit;
	}
	else {
		VerDisLim = 0;
		HorDisLim = 0;
	}
	CurVer = 0;
	CurHor = 0;
	PlayerStartPoint = ShipCharacter->GetActorLocation();
}

void AC_SystemCharacterController::ResetPlayer(){
	if (ShipCharacter){
		ShipCharacter->SetActorLocation(PlayerStartPoint);
		ShipCharacter->CollisionCom->SetPhysicsLinearVelocity(FVector::ZeroVector);
		ShipCharacter->SetActorRotation(FRotator::ZeroRotator);
	}
}

bool AC_SystemCharacterController::DistanceCheck(){
	if (VerDisLim == 0 || HorDisLim == 0){
		return false;
	}
	FVector CurPosition = ShipCharacter->GetActorLocation();
	CurHor = abs(CurPosition.Z);
	CurPosition.Z = 0;
	CurVer = CurPosition.Size();

	if (CurHor > HorDisLim || CurVer > VerDisLim)
		return true;
	if (ShipUI) {
		if (ShipUI->Bar_Vertical)ShipUI->Bar_Vertical->SetPercent(CurVer/VerDisLim);
		if (ShipUI->Bar_Horizontal)ShipUI->Bar_Horizontal->SetPercent(CurHor/HorDisLim);
	}
	return false;
}

void AC_SystemCharacterController::SetupInputComponent() {
	Super::SetupInputComponent();

	InputComponent->BindAxis("ShipSpeedUp",this, &AC_SystemCharacterController::ShipSpeedUp);
}

void AC_SystemCharacterController::ShipSpeedUp(float value){
	if (ShipCharacter){
		double Deltatime = FApp::GetDeltaTime();
		if (value == 0) {
			if (ShipCharacter->SpringArmCom->TargetArmLength > 300)
				ShipCharacter->SpringArmCom->TargetArmLength -= ArmChangeRate * Deltatime;
			if (ShipCharacter->CameraCom->FieldOfView < 90)
				ShipCharacter->CameraCom->FieldOfView += CameraChangeRate * Deltatime;

			if (CurSpeedUpTime < SpeedUptime)
				CurSpeedUpTime += Deltatime;
			else if (CurSpeedUpTime > SpeedUptime)
				CurSpeedUpTime = SpeedUptime;

			ShipCharacter->SpeedUpRate = 500;

		}
		else if ( CurSpeedUpTime < 0.01){
			if (ShipCharacter->SpringArmCom->TargetArmLength > 300)
				ShipCharacter->SpringArmCom->TargetArmLength -= ArmChangeRate * Deltatime;
			if (ShipCharacter->CameraCom->FieldOfView < 90)
				ShipCharacter->CameraCom->FieldOfView += CameraChangeRate * Deltatime;
			ShipCharacter->SpeedUpRate = 700;
		}
		else if ( CurSpeedUpTime > 0){
			if (ShipCharacter->SpringArmCom->TargetArmLength < 420)
				ShipCharacter->SpringArmCom->TargetArmLength += ArmChangeRate * Deltatime;
			if (ShipCharacter->CameraCom->FieldOfView > 70)
				ShipCharacter->CameraCom->FieldOfView -= CameraChangeRate * Deltatime;

			if (CurSpeedUpTime > 0)
				CurSpeedUpTime -= Deltatime;
			else if (CurSpeedUpTime < 0)
				CurSpeedUpTime = 0;

			ShipCharacter->SpeedUpRate = 1000;
		}

		if (ShipUI && ShipUI->Bar_Speed)
			ShipUI->Bar_Speed->SetPercent(CurSpeedUpTime / SpeedUptime);
	}
	if (DistanceCheck()){
		ResetPlayer();
	}
}

#pragma region Widget about Overlap With Star
void AC_SystemCharacterController::OverlapStar(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool FromSweep, const FHitResult& HitRusult)
{
	AC_NormalPlanetPawn* tempStar = Cast<AC_NormalPlanetPawn>(OtherActor);
	if (tempStar) {
		if (StarInfor) {
			if (StarInfor->TextBlock_Name) StarInfor->TextBlock_Name->SetText(FText::FromString(tempStar->StarName));
			if (StarInfor->TextBlock_Intro)StarInfor->TextBlock_Intro->SetText(FText::FromString(tempStar->StarIntrodoce));;
			if (StarInfor->Image_Pic)	   StarInfor->Image_Pic->SetBrushFromTexture(tempStar->StarPicture);
			if (tempStar->StarName != "")  TargetMapName = tempStar->StarMap;
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
	UGameplayStatics::OpenLevel(GetWorld(), *TargetMapName);
}
#pragma endregion