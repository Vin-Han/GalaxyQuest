#include "../Public/Character/C_SystemCharacterController.h"

#include "../Public/Character/C_SystemCharacter.h"
#include "../Public/Planet/C_NormalPlanetPawn.h"
#include "../Public/Widget/C_StarIntroduce_UI.h"
#include "../Public/Widget/C_SolarUserFace.h"
#include "../Public/GameMode/C_SolarSystemGameMode.h"
#include "../Public/Projectile/C_Bullet_Base.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

void AC_SystemCharacterController::BeginPlay()
{
	Super::BeginPlay();
	CleanupGameViewport();
	InitializeShip();
	InitializeStarWidget();
	InitializeShipWidget();

	TargetMapName = "/Game/Blueprint/BP_Map/BP_Test_Map";
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Hello,StartGameMode"));

	if (ShipCharacter->BulletList.Num() > 0)
	{
		CurrentBullet = ShipCharacter->BulletList[0];
		CurrentIndex = 0;
	}
}

void AC_SystemCharacterController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UpdateSpeedState(DeltaSeconds);
}

#pragma region Initialize Controller
void AC_SystemCharacterController::InitializeShip()
{
	ShipCharacter = Cast<AC_SystemCharacter>(GetPawn());
	if (ShipCharacter)
	{
		ShipCharacter->CollisionCom->OnComponentBeginOverlap.AddDynamic(this,&AC_SystemCharacterController::OverlapStar);
		
		SpeedGap = ShipCharacter->MaxSpeed * ShipCharacter->MaxSpeedRate;
		CurSpeed = 0;

		ShipCharacter->CameraSpeed		= FMath::Clamp(ShipCharacter->CameraSpeed, 0.01f, 5.0f);
		ShipCharacter->RotateSpeed		= FMath::Clamp(ShipCharacter->RotateSpeed, 0.1f, 2.0f);
		ShipCharacter->MaxSpeedRate		= FMath::Max(ShipCharacter->MaxSpeedRate, 0.1f);
		ShipCharacter->AccelerationRate = FMath::Max(ShipCharacter->AccelerationRate, 0.1f);

		ShipCharacter->ShipMovement->MaxSpeed	  = ShipCharacter->MaxSpeed;
		ShipCharacter->ShipMovement->Acceleration = ShipCharacter->Acceleration;
		ShipCharacter->ShipMovement->Deceleration = ShipCharacter->DecayRate;

		ArmBaseLength = ShipCharacter->SpringArmCom->TargetArmLength;
		ArmMinLength = FMath::Max(ArmBaseLength * ShipCharacter->ArmChangeRatio, 0.0f);
		ArmLenChangeRate = FMath::Abs(ArmBaseLength - ArmMinLength) / ShipCharacter->ChangeDuration;

		CamBaseField  = ShipCharacter->CameraCom->FieldOfView;
		CamMaxField = FMath::Max(CamBaseField * ShipCharacter->CameraChangeRatio, 0.0f);
		CamAngChangeRate = FMath::Abs(CamBaseField - CamMaxField) / ShipCharacter->ChangeDuration;

		RushLeft = ShipCharacter->MaxRushTime;
		RushRevertRate = ShipCharacter->MaxRushTime / ShipCharacter->RushTimeRevertTime;
		RushLestAlarm = ShipCharacter->MaxRushTime * ShipCharacter->RushLeftAlarmRate;

		bIsSpeedUpMode = false;
		bIsRevertMode = false;
	}
}

void AC_SystemCharacterController::InitializeStarWidget()
{
	StarInfor = CreateWidget<UC_StarIntroduce_UI>(GetGameInstance(), 
				LoadClass<UC_StarIntroduce_UI>(nullptr, TEXT("WidgetBlueprint'/Game/UI/SolarSystemUI/BP_StarIntroduction.BP_StarIntroduction_c'")));
	if (StarInfor)
	{
		if (StarInfor->Button_Close)
		{
			StarInfor->Button_Close->OnClicked.AddDynamic(this, &AC_SystemCharacterController::StarCloseBtnOnClicked);
		}
		if (StarInfor->Button_Explore)
		{
		StarInfor->Button_Explore->OnClicked.AddDynamic(this, &AC_SystemCharacterController::StarExploreBtnOnClicked);
		}
	}
}

void AC_SystemCharacterController::InitializeShipWidget()
{
	ShipUI = CreateWidget<UC_SolarUserFace>(GetGameInstance(),
											LoadClass<UC_SolarUserFace>(nullptr, TEXT("WidgetBlueprint'/Game/UI/SolarSystemUI/BP_SolarUserFace.BP_SolarUserFace_c'")));
	if (ShipUI)
	{
		ShipUI->AddToViewport();
		if (ShipUI->Bar_SpeedUp)   ShipUI->Bar_SpeedUp	 ->SetPercent(1.f);
		if (ShipUI->Bar_Speed)	   ShipUI->Bar_Speed	 ->SetPercent(0.f);
		if (ShipUI->Bar_ExtraSpeed)ShipUI->Bar_ExtraSpeed->SetPercent(0.f);
		if (ShipUI->Bar_Horizontal)ShipUI->Bar_Horizontal->SetPercent(1.f);
	}
}

#pragma endregion

void AC_SystemCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("UpDown", this, &AC_SystemCharacterController::MouseUpDown);
	InputComponent->BindAxis("RightLeft", this, &AC_SystemCharacterController::MouseRightLeft);
	InputComponent->BindAxis("MoveForward", this, &AC_SystemCharacterController::MoveForward);
	InputComponent->BindAxis("MoveTurn", this, &AC_SystemCharacterController::MoveTurn);
	InputComponent->BindAxis("MoveUpDown", this, &AC_SystemCharacterController::MoveUpDown);

	InputComponent->BindAction("ShipSpeedUpEnd", EInputEvent::IE_Pressed, this, &AC_SystemCharacterController::ShipSpeedUp);
	InputComponent->BindAction("ShipSpeedUpEnd", EInputEvent::IE_Released, this, &AC_SystemCharacterController::ShipSpeedEnd);

	InputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &AC_SystemCharacterController::Fire);
	InputComponent->BindAction("ChangeBulletAdd", EInputEvent::IE_Pressed, this, &AC_SystemCharacterController::ChangeBulletAdd);
	InputComponent->BindAction("ChangeBulletExtract", EInputEvent::IE_Pressed, this, &AC_SystemCharacterController::ChangeBulletExtract);
}

#pragma region Ship Move Relatived
void AC_SystemCharacterController::MouseUpDown(float value) 
{
	AddYawInput(value * ShipCharacter->CameraSpeed);
}

void AC_SystemCharacterController::MouseRightLeft(float value) 
{
	AddPitchInput(value * ShipCharacter->CameraSpeed);
}

void AC_SystemCharacterController::MoveTurn(float value) 
{
	FRotator temp = FRotator::ZeroRotator;
	float rSpeedLimit = CurSpeed
					  / ShipCharacter->ShipMovement->MaxSpeed;
	temp.Yaw = rSpeedLimit * (ShipCharacter->RotateSpeed * value);
	ShipCharacter->AddActorWorldRotation(temp);
}

void AC_SystemCharacterController::MoveUpDown(float value) 
{
	FRotator temp = FRotator::ZeroRotator;
	float rSpeedLimit = CurSpeed
		/ ShipCharacter->ShipMovement->MaxSpeed;
	temp.Pitch = rSpeedLimit * (ShipCharacter->RotateSpeed * value);
	ShipCharacter->AddActorLocalRotation(temp);
}

void AC_SystemCharacterController::MoveForward(float value) 
{
	FVector temp = ShipCharacter->GetActorForwardVector();
	if (CurSpeed < ShipCharacter->ShipMovement->MaxSpeed)
	{
		ShipCharacter->AddMovementInput(temp, value);
	}
}

void AC_SystemCharacterController::ShipSpeedUp()
{
	if (!bIsRevertMode)
	{
		bIsSpeedUpMode = true;
		ShipCharacter->ShipMovement->MaxSpeed = ShipCharacter->MaxSpeed + SpeedGap;
		ShipCharacter->ShipMovement->Acceleration = ShipCharacter->Acceleration * ShipCharacter->AccelerationRate;
	}
}

void AC_SystemCharacterController::ShipSpeedEnd()
{
	bIsSpeedUpMode = false;
	ShipCharacter->ShipMovement->MaxSpeed = ShipCharacter->MaxSpeed;
	ShipCharacter->ShipMovement->Acceleration = ShipCharacter->Acceleration;
}

void AC_SystemCharacterController::UpdateSpeedState(float DeltaSeconds)
{
	CurSpeed = ShipCharacter->GetVelocity().Size();
	if ( RushLeft <= 0 )
	{
		bIsRevertMode = true;
		ShipSpeedEnd();
	}
	else if (bIsRevertMode && RushLeft > RushLestAlarm)
	{
		bIsRevertMode = false;
	}

	RushLeft += !bIsSpeedUpMode ? ( RushRevertRate * DeltaSeconds ):( -RushRevertRate * DeltaSeconds );
	RushLeft = FMath::Min(RushLeft, ShipCharacter->MaxRushTime);
	if (ShipUI && ShipUI->Bar_SpeedUp) 
	{
		if (RushLeft < RushLestAlarm)
		{
			ShipUI->Bar_SpeedUp->SetFillColorAndOpacity(FLinearColor(FColor::Red));
		}
		else
		{
			ShipUI->Bar_SpeedUp->SetFillColorAndOpacity(FLinearColor(FColor::Green));
		}
		ShipUI->Bar_SpeedUp->SetPercent(RushLeft / ShipCharacter->MaxRushTime);
	}
	if (ShipUI && ShipUI->Bar_Speed) 
	{
		float temp = FMath::Min(CurSpeed / ShipCharacter->MaxSpeed , 1.0f);
		ShipUI->Bar_Speed->SetPercent(temp);
		if (ShipUI->Bar_ExtraSpeed && temp == 1)
		{
			float extra = (CurSpeed - ShipCharacter->MaxSpeed) / (SpeedGap);
			ShipUI->Bar_ExtraSpeed->SetPercent(extra);
		}
	}

	if (bIsSpeedUpMode){
		if (ShipCharacter->SpringArmCom->TargetArmLength > ArmMinLength)
		{
			ShipCharacter->SpringArmCom->TargetArmLength -= ArmLenChangeRate * DeltaSeconds;
		}
		if (ShipCharacter->CameraCom->FieldOfView < CamMaxField) 
		{
			ShipCharacter->CameraCom->FieldOfView += CamAngChangeRate * DeltaSeconds;
		}
	}
	else{
		if (ShipCharacter->SpringArmCom->TargetArmLength < ArmBaseLength) 
		{
			ShipCharacter->SpringArmCom->TargetArmLength += ArmLenChangeRate * DeltaSeconds;
		}
		if (ShipCharacter->CameraCom->FieldOfView > CamBaseField) 
		{
			ShipCharacter->CameraCom->FieldOfView -= CamAngChangeRate * DeltaSeconds;
		}
	}

}

#pragma endregion

#pragma region Widget about Overlap With Star
void AC_SystemCharacterController::OverlapStar(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool FromSweep, const FHitResult& HitRusult)
{
	if (ShipCharacter->bIsInWarMode)
	{
		return;
	}
	AC_NormalPlanetPawn* tempStar = Cast<AC_NormalPlanetPawn>(OtherActor);
	if (tempStar) 
	{
		if (StarInfor) 
		{
			if (StarInfor->TextBlock_Name) 
			{
				StarInfor->TextBlock_Name->SetText(FText::FromString(tempStar->StarName));
			}
			if (StarInfor->TextBlock_Intro)
			{
				StarInfor->TextBlock_Intro->SetText(FText::FromString(tempStar->StarIntrodoce));
			}
			if (StarInfor->Image_Pic) 
			{ 
				StarInfor->Image_Pic->SetBrushFromTexture(tempStar->StarPicture); 
			}
			if (tempStar->StarName != "")  
			{
				TargetMapName = tempStar->StarMap;
			}
			UGameplayStatics::SetGamePaused(this,true);
			bShowMouseCursor = true;
			StarInfor->AddToViewport();
		}
	}
}

void AC_SystemCharacterController::StarCloseBtnOnClicked()
{
	UGameplayStatics::SetGamePaused(this, false);
	bShowMouseCursor = false;
	StarInfor->RemoveFromViewport();
}

void AC_SystemCharacterController::StarExploreBtnOnClicked()
{
	UGameplayStatics::SetGamePaused(this, false);
	bShowMouseCursor = false;
	StarInfor->RemoveFromViewport();
	UGameplayStatics::OpenLevel(GetWorld(), *TargetMapName);
}

#pragma endregion

#pragma region Fire Relatied
void AC_SystemCharacterController::Fire()
{
	if (CurrentBullet)
	{
		FireLocation = ShipCharacter->ShipMesh->GetSocketLocation(TEXT("BulletSpawner"));
		FireRotation = ShipCharacter->CollisionCom->GetComponentRotation();
		AC_Bullet_Base* test = Cast<AC_Bullet_Base>(
		GetWorld()->SpawnActor(CurrentBullet, &FireLocation, &FireRotation) );
		if (test)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s"), *(test->BulletName));
		}
	}
}

void AC_SystemCharacterController::ChangeBulletAdd()
{
	if (ShipCharacter->BulletList.Num() > 0)
	{
		if (CurrentIndex == ShipCharacter->BulletList.Num() - 1)
		{
			CurrentBullet = ShipCharacter->BulletList[0];
			CurrentIndex = 0;
		}
		else
		{
			CurrentBullet = ShipCharacter->BulletList[CurrentIndex+1];
			CurrentIndex ++;
		}
	}
}

void AC_SystemCharacterController::ChangeBulletExtract()
{
	if (ShipCharacter->BulletList.Num() > 0)
	{
		if (CurrentIndex == 0)
		{
			CurrentBullet = ShipCharacter->BulletList[ShipCharacter->BulletList.Num() - 1];
			CurrentIndex = ShipCharacter->BulletList.Num() - 1;
		}
		else
		{
			CurrentBullet = ShipCharacter->BulletList[CurrentIndex - 1];
			CurrentIndex--;
		}
	}
}

#pragma endregion