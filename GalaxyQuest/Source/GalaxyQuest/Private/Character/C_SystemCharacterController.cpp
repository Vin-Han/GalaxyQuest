#include "../Public/Character/C_SystemCharacterController.h"

#include "../Public/Character/C_SystemCharacter.h"
#include "../Public/Character/C_SystemCharacterState.h"
#include "../Public/Planet/C_NormalPlanetPawn.h"

#include "../Public/Widget/C_StarIntroduce_UI.h"
#include "../Public/Widget/C_SolarUserFace.h"
#include "../Public/Widget/C_UserBag.h"
#include "../Public/Widget/C_SingleItem.h"
#include "../Public/Widget/C_StarLocation_UI.h"
#include "../Public/Widget/C_ShopPage.h"

#include "../Public/GameMode/C_SolarSystemGameMode.h"
#include "../Public/Projectile/C_Bullet_Base.h"
#include "../Public/Projectile/C_Bullet_EnemyNormal.h"
#include "../Public/Shield/C_Shield_Base.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/ScrollBox.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Engine/Engine.h"

void AC_SystemCharacterController::BeginPlay()
{
	Super::BeginPlay();
	CleanupGameViewport();

	InitializeShip();
	InitializeShipState();

	InitializeStarWidget();
	InitializeShipWidget();
	InitializeBagWidget();
	InitializeShipMessage();

	InitializeBulletWindow();
	InitializeBaseSheild();

	WarTimeDelaySecond = 3.0;
	TargetMapName = "/Game/Blueprint/BP_Map/BP_Test_Map";
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Hello,StartGameMode"));
}

void AC_SystemCharacterController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	UpdateSpeedState(DeltaSeconds);
	UpdateBulletLoadingTime(DeltaSeconds);
	UpdatePlayerState();
}

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

	InputComponent->BindAction("OpenBag", EInputEvent::IE_Pressed, this, &AC_SystemCharacterController::BagOpen_Function);
	InputComponent->BindAction("OpenStarPage", EInputEvent::IE_Pressed, this, &AC_SystemCharacterController::OpenStarWidget);
}

#pragma region Initialize Controller
void AC_SystemCharacterController::InitializeShip()
{
	ShipCharacter = Cast<AC_SystemCharacter>(GetPawn());
	if (ShipCharacter)
	{
		ShipCharacter->CollisionCom->OnComponentBeginOverlap.AddDynamic(this,&AC_SystemCharacterController::OverlapWithStar);
		ShipCharacter->CollisionCom->OnComponentEndOverlap.AddDynamic(this, &AC_SystemCharacterController::EndOverlapWithStar);

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

void AC_SystemCharacterController::InitializeShipState()
{
	ShipState = Cast<AC_SystemCharacterState>(this->PlayerState);
	if (ShipState)
	{
		//GenerateBulletList();
		//GenerateShieldList();
		ShipState->PlayerCurrentHp = ShipCharacter->TotalHP;
		ShipState->Money = 999;
	}
}

void AC_SystemCharacterController::InitializeStarWidget()
{
	StarInfor = CreateWidget<UC_StarIntroduce_UI>(GetGameInstance(), 
				LoadClass<UC_StarIntroduce_UI>(nullptr, TEXT("WidgetBlueprint'/Game/UI/SolarSystemUI/BP_StarIntroduction.BP_StarIntroduction_c'")));
	if (StarInfor)
	{
		bIfCanOpenStarPage = false;
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
		if (ShipUI->Bar_SpeedUp) 
		{
			ShipUI->Bar_SpeedUp->SetPercent(1.f);
		}
		if (ShipUI->Bar_Speed)
		{
			ShipUI->Bar_Speed->SetPercent(0.f);
		}
		if (ShipUI->Bar_ExtraSpeed)
		{
			ShipUI->Bar_ExtraSpeed->SetPercent(0.f);
		}
		if (ShipUI->Bar_Horizontal)
		{
			ShipUI->Bar_Horizontal->SetPercent(1.f);
		}
		if (ShipUI->Bar_Blood)
		{
			ShipUI->Bar_Blood->SetPercent(1.f);
		}
		if (ShipUI->Bar_Shield)
		{
			ShipUI->Bar_Shield->SetPercent(1.f);
		}
	}
}

void AC_SystemCharacterController::InitializeBagWidget()
{
	ShipBag = CreateWidget<UC_UserBag>(GetGameInstance(), LoadClass<UC_UserBag>(nullptr,
		TEXT("WidgetBlueprint'/Game/UI/SolarSystemUI/BP_UserBag.BP_UserBag_c'")));
	if (ShipBag)
	{
		ShipBag->Exit_Btn->OnClicked.AddDynamic(this, &AC_SystemCharacterController::BagBtn_CloseWindow);

	}
}

void AC_SystemCharacterController::InitializeShipMessage()
{
	ShipMassage = CreateWidget<UC_StarLocation_UI>(GetGameInstance(), LoadClass<UC_StarLocation_UI>(nullptr,
		TEXT("WidgetBlueprint'/Game/UI/SolarSystemUI/BP_StarLocation.BP_StarLocation_c'")));
	if (ShipMassage)
	{
		ShipMassage->Text_StarDistance->SetText(FText::FromString(""));
		ShipMassage->Text_StarLocation->SetText(FText::FromString("Player Warning Message"));
	}
}

void AC_SystemCharacterController::InitializeBulletWindow()
{
	for (int i = 0; i < BAG_SIZE; i++)
	{
		curBulletList[i] = nullptr;
	}

	CurrentIndex = 0;
	if (ShipUI)
	{
		for (int i = 0; i < BAG_SIZE; i++)
		{
			ShipUI->BulletOut[i]->SetVisibility(ESlateVisibility::Hidden);
			ShipUI->BulletPic[i]->SetOpacity(0.5f);
			ShipUI->BulletPic[i]->SetVisibility(ESlateVisibility::Hidden);
			ShipUI->BulletCD[i]->SetVisibility(ESlateVisibility::Hidden);
			ShipUI->BulletNum[i]->SetVisibility(ESlateVisibility::Hidden);
			ShipUI->BulletNum[i]->SetOpacity(0.8f);
			ChangeBulletWindow(i, false);
		}
	}
	ChangeBulletWindow(CurrentIndex, true);
}

void AC_SystemCharacterController::InitializeBaseSheild()
{
	ShipState->CurrentEqipedShield = nullptr;
	GenerateNewShield();
}

#pragma endregion

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
	temp.Yaw = rSpeedLimit * (ShipCharacter->RotateSpeed*0.8 * value);
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
void AC_SystemCharacterController::OverlapWithStar(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex, bool FromSweep, const FHitResult& HitRusult)
{
	if (ShipCharacter->bIsInWarMode)
	{
		return;
	}
	AC_NormalPlanetPawn* tempStar = Cast<AC_NormalPlanetPawn>(OtherActor);
	if (tempStar && StarInfor)
	{
		GenerateShopList(tempStar);
		RefleshStarIntro(tempStar);
	}
}

void AC_SystemCharacterController::EndOverlapWithStar(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 BodyIndex)
{
	if (ShipMassage->IsInViewport() == true)
	{
		ShipMassage->RemoveFromViewport();
	}
	AC_NormalPlanetPawn* tempStar = Cast<AC_NormalPlanetPawn>(OtherActor);
	if (tempStar)
	{
		ResetStarShop(tempStar);
		bIfCanOpenStarPage = false;
	}
	
}

void AC_SystemCharacterController::OpenStarWidget()
{
	if (ShipCharacter->bIsInWarMode == false && bIfCanOpenStarPage && StarInfor)
	{
		UGameplayStatics::SetGamePaused(this, true);
		bShowMouseCursor = true;
		if (StarInfor->IsInViewport() == false)
		{
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

void AC_SystemCharacterController::RefleshStarIntro(AC_NormalPlanetPawn* tempStar)
{
	StarInfor->TextBlock_Name->SetText(FText::FromString(tempStar->StarName));
	StarInfor->TextBlock_Intro->SetText(FText::FromString(tempStar->StarIntrodoce));
	StarInfor->Image_Pic->SetBrushFromTexture(tempStar->StarPicture);
	TargetMapName = tempStar->StarMap;

	bIfCanOpenStarPage = true;
	if (ShipMassage->IsInViewport() == false)
	{
		ShipMassage->AddToViewport();
	}
	ShipMassage->Text_StarLocation->SetText(FText::FromString("Press [F] to open star detail surface."));
}

#pragma endregion

#pragma region Fire Relatied
void AC_SystemCharacterController::ChangeBulletWindow(float WindowIndex, bool bIsUpgrade)
{
	if (ShipUI)
	{
		if (bIsUpgrade)
		{
			ShipUI->BulletOut[WindowIndex]->SetColorAndOpacity(FColor::White);
			ShipUI->BulletOut[WindowIndex]->SetBrushSize(FVector2D(BULLET_WINDOW_SIZE * 1.05));
			ShipUI->BulletPic[WindowIndex]->SetOpacity(1.0f);
			ShipUI->BulletPic[WindowIndex]->SetBrushSize(FVector2D(BULLET_WINDOW_SIZE * 1.05));
			ShipUI->BulletNum[WindowIndex]->SetOpacity(1.0f);
		}
		else
		{
			ShipUI->BulletOut[WindowIndex]->SetColorAndOpacity(FColor::Black);
			ShipUI->BulletOut[WindowIndex]->SetBrushSize(FVector2D(BULLET_WINDOW_SIZE));
			ShipUI->BulletPic[WindowIndex]->SetOpacity(0.5f);
			ShipUI->BulletPic[WindowIndex]->SetBrushSize(FVector2D(BULLET_WINDOW_SIZE));
			ShipUI->BulletNum[WindowIndex]->SetOpacity(0.8f);
		}
	}
}

void AC_SystemCharacterController::Fire()
{
	if (BulletStateCheck() == true)
	{
		FVector FireLocation = ShipCharacter->ShipMesh->GetSocketLocation(TEXT("BulletSpawner"));
		FRotator FireRotation = ShipCharacter->CollisionCom->GetComponentRotation();

		AC_Bullet_Base* test = Cast<AC_Bullet_Base>(
			GetWorld()->SpawnActor(curBulletList[CurrentIndex]->BulletClass,
				&FireLocation, &FireRotation));

		curBulletList[CurrentIndex]->CurrentAccout --;
		curBulletList[CurrentIndex]->CurrentLoadingTime =
			curBulletList[CurrentIndex]->BulletClass.GetDefaultObject()->BulletLoadingTime;
	}
	ChangeWarMode();
}

void AC_SystemCharacterController::ChangeBulletAdd()
{
	ChangeBulletWindow(CurrentIndex, false);
	CurrentIndex++;
	if (CurrentIndex == BAG_SIZE || 
		curBulletList[CurrentIndex] == nullptr)
	{
		CurrentIndex = 0;
	}
	ChangeBulletWindow(CurrentIndex, true);
}

void AC_SystemCharacterController::ChangeBulletExtract()
{
	ChangeBulletWindow(CurrentIndex, false);
	if (CurrentIndex == 0)
	{
		for (int i = BAG_SIZE - 1; i >= 0; i--)
		{
			if (curBulletList[i] != nullptr)
			{
				CurrentIndex = i;
				break;
			}
		}
	}
	else
	{
		CurrentIndex--;
	}
	ChangeBulletWindow(CurrentIndex, true);
}

bool AC_SystemCharacterController::BulletStateCheck()
{
	if (curBulletList[CurrentIndex] != nullptr
		&& curBulletList[CurrentIndex]->CurrentAccout > 0
		&& curBulletList[CurrentIndex]->CurrentLoadingTime <= 0
		)
	{
		return true;
	}
	UE_LOG(LogTemp, Warning, TEXT("FireNotAllow"));
	return false;
}

void AC_SystemCharacterController::UpdateBulletLoadingTime(float DeltaSeconds)
{
	if (UGameplayStatics::IsGamePaused(GetWorld()))
	{
		return;
	}
	for (int i = 0; i < ShipState->BulletList.Num(); i++)
	{
		if (ShipState->BulletList[i].CurrentLoadingTime != 0.0f)
		{
			ShipState->BulletList[i].CurrentLoadingTime =
				FMath::Max(0.f,
					ShipState->BulletList[i].CurrentLoadingTime - DeltaSeconds);
		}
	}
	for (int i = 0; i < BAG_SIZE; i++)
	{
		if (curBulletList[i] != nullptr)
		{
			ShipUI->BulletCD[i]->SetPercent(
				curBulletList[i]->CurrentLoadingTime /
				curBulletList[i]->BulletClass.GetDefaultObject()->BulletLoadingTime);
			ShipUI->BulletNum[i]->SetText(FText::FromString(
				FString::FromInt(curBulletList[i]->CurrentAccout)));
		}
		else
		{
			break;
		}
	}
}

void AC_SystemCharacterController::UpdateBulletWindow()
{
	for (int i = 0; i < BAG_SIZE; i++)
	{
		ShipUI->BulletOut[i]->SetVisibility(ESlateVisibility::Hidden);
		ShipUI->BulletPic[i]->SetVisibility(ESlateVisibility::Hidden);
		ShipUI->BulletCD[i]->SetVisibility(ESlateVisibility::Hidden);
		ShipUI->BulletNum[i]->SetVisibility(ESlateVisibility::Hidden);
		ChangeBulletWindow(i, false);
	}

	for (int i = 0; i < BAG_SIZE; i++)
	{
		if (curBulletList[i] != nullptr)
		{
			ShipUI->BulletOut[i]->SetVisibility(ESlateVisibility::Visible);
			ShipUI->BulletPic[i]->SetVisibility(ESlateVisibility::Visible);
			ShipUI->BulletCD[i]->SetVisibility(ESlateVisibility::Visible);
			ShipUI->BulletNum[i]->SetVisibility(ESlateVisibility::Visible);

			ShipUI->BulletPic[i]->SetBrushFromTexture(curBulletList[i]->BulletClass.GetDefaultObject()->BulletPicture);
			ShipUI->BulletNum[i]->SetText(FText::FromString(
				FString::FromInt(curBulletList[i]->CurrentAccout)));

			ChangeBulletWindow(i, false);
		}
	}
	CurrentIndex = 0;
	ChangeBulletWindow(CurrentIndex, true);
}

void AC_SystemCharacterController::ChangeWarMode()
{
	if (ShipCharacter)
	{
		ShipCharacter->bIsInWarMode = true;
		UE_LOG(LogTemp, Warning, TEXT("BeginWar"));
		GetWorld()->GetTimerManager().SetTimer(TH_ChangeWarMode,this,&AC_SystemCharacterController::DelayModeChange,1,false, WarTimeDelaySecond);
	}
}

void AC_SystemCharacterController::DelayModeChange()
{
	if (ShipCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("EndWar"));
		ShipCharacter->bIsInWarMode = false;
	}
}

float AC_SystemCharacterController::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (Cast<AC_Bullet_EnemyNormal>(DamageCauser))
	{
		CalculateDamage(Damage);
	}
	ChangeWarMode();
	return 0.0f;
}

#pragma endregion

#pragma region Shield Related
void AC_SystemCharacterController::GenerateNewShield(FSheildBagItem* newShield)
{
	if (newShield == nullptr)
	{
		if (ShipState->CurrentEqipedShield)
		{
			ShipState->CurrentEqipedShield->SetEqipState(true);
			ShipState->CurrentEqipedShield->ShieldMesh->SetVisibility(true);
		}
		return;
	}
	if (ShipState->CurrentEqipedShield)
	{
		if (ShipState->CurrentEqipedShield->ShieldName == newShield->ShieldClass.GetDefaultObject()->ShieldName)
		{
			ShipState->CurrentEqipedShield->SetEqipState(true);
			ShipState->CurrentEqipedShield->ShieldMesh->SetVisibility(true);
			return;
		}
		else
		{
			ShipState->CurrentEqipedShield->Destroy();
			ShipState->CurrentEqipedShield = nullptr;
		}
	}
	ShipState->CurrentEqipedShield = Cast<AC_Shield_Base>(GetWorld()->SpawnActor(newShield->ShieldClass));
	ShipState->CurrentEqipedShield->AttachToComponent(ShipCharacter->ShipMesh,
		FAttachmentTransformRules::KeepRelativeTransform);
	ShipState->CurrentEqipedShield->SetActorRelativeScale3D(FVector(1.05f, 1.05f, 1.05f));
	ShipState->CurrentEqipedShield->SetEqipState(true);
}

void AC_SystemCharacterController::CalculateDamage(float Damage, bool bIfCalculateExtraDamage)
{
	if (ShipState->CurrentEqipedShield && 
		ShipState->CurrentEqipedShield->bIsEqiped == true && 
		ShipState->CurrentEqipedShield->CurrentShield > 0)
	{
		ShipState->CurrentEqipedShield->AfterTakeDamage();
		ShipState->CurrentEqipedShield->CurrentShield -= Damage;
		if (bIfCalculateExtraDamage && ShipState->CurrentEqipedShield->CurrentShield < 0)
		{
			ShipState->PlayerCurrentHp -= ShipState->CurrentEqipedShield->CurrentShield;
			ShipState->CurrentEqipedShield->CurrentShield = 0;
			ShipState->CurrentShield = 0;
		}
		else
		{
			ShipState->CurrentShield = ShipState->CurrentEqipedShield->CurrentShield;
		}
	}
	else
	{
		ShipState->PlayerCurrentHp -= Damage;
	}

	if (ShipState->PlayerCurrentHp < 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Should Die"));
	}
}

void AC_SystemCharacterController::UpdatePlayerState()
{
	if (ShipState && ShipUI)
	{
		ShipUI->Bar_Blood->SetPercent( 
			ShipState->PlayerCurrentHp / ShipCharacter->TotalHP);

		if (ShipState->CurrentEqipedShield && 
			ShipState->CurrentEqipedShield->bIsEqiped == true)
		{
			ShipState->CurrentShield = ShipState->CurrentEqipedShield->CurrentShield;
			ShipUI->Bar_Shield->SetPercent(
				ShipState->CurrentEqipedShield->CurrentShield / ShipState->CurrentEqipedShield->TotalShield);
		}
		else
		{
			ShipUI->Bar_Shield->SetPercent(0);
		}


		if (ShipUI->Bar_Blood->Percent < 0.2)
		{
			ShipUI->Bar_Blood->SetFillColorAndOpacity(FLinearColor(FColor::Red));
		}
		else
		{
			ShipUI->Bar_Blood->SetFillColorAndOpacity(FLinearColor(FColor::Green));
		}

		if (ShipUI->Bar_Shield->Percent < 0.2)
		{
			ShipUI->Bar_Shield->SetFillColorAndOpacity(FLinearColor(FColor::Red));
		}
		else
		{
			ShipUI->Bar_Shield->SetFillColorAndOpacity(FLinearColor(FColor::Yellow));
		}
	}

}
#pragma endregion

#pragma region Bag related Function
void AC_SystemCharacterController::BagBtn_CloseWindow()
{
	if (UGameplayStatics::IsGamePaused(GetWorld()))
	{
		UGameplayStatics::SetGamePaused(this, false);
	}
	curSheildPtr = nullptr;
	curBulletPtr = nullptr;
	ShipBag->Left_Roll->ClearChildren();
	ShipBag->Left_Btn->OnClicked.RemoveAll(this);
	ShipBag->Right_Btn->OnClicked.RemoveAll(this);
	bShowMouseCursor = false;
	ShipBag->RemoveFromViewport();
}

void AC_SystemCharacterController::BagOpen_Function()
{
	if (ShipBag)
	{
		if (ShipBag->IsInViewport() == false)
		{
			CreatItemList();
			LoadPlayerBagState();
			ShipBag->AddToViewport();
			if (UGameplayStatics::IsGamePaused(GetWorld()) == false)
			{
				UGameplayStatics::SetGamePaused(this, true);
			}
			bShowMouseCursor = true;

		}
	}
}

void AC_SystemCharacterController::ShowItemInformation()
{
	if (ShipBag)
	{
		ShipBag->Left_Btn->OnClicked.RemoveAll(this);
		ShipBag->Right_Btn->OnClicked.RemoveAll(this);
		if (curSheildPtr)
		{
			ShipBag->Intro_Text->SetText(FText::FromString(curSheildPtr->ShieldClass.GetDefaultObject()->ShieldName));
			ShipBag->Load_Image->SetBrushFromTexture(curSheildPtr->ShieldClass.GetDefaultObject()->ShieldPicture);
			ShipBag->LeftBtn_Text->SetText(FText::FromString("Install"));
			ShipBag->Left_Btn->OnClicked.AddDynamic(this,&AC_SystemCharacterController::ShieldSetEquip);
			ShipBag->RightBtn_Text->SetText(FText::FromString("Uninstall"));
			ShipBag->Right_Btn->OnClicked.AddDynamic(this, &AC_SystemCharacterController::ShieldEndEquip);
		}
		else if (curBulletPtr)
		{
			ShipBag->Intro_Text->SetText(FText::FromString(curBulletPtr->BulletClass.GetDefaultObject()->BulletName));
			ShipBag->Load_Image->SetBrushFromTexture(curBulletPtr->BulletClass.GetDefaultObject()->BulletPicture);
			ShipBag->LeftBtn_Text->SetText(FText::FromString("Load"));
			ShipBag->Left_Btn->OnClicked.AddDynamic(this, &AC_SystemCharacterController::BulletSetEquip);
			ShipBag->RightBtn_Text->SetText(FText::FromString("Unload"));
			ShipBag->Right_Btn->OnClicked.AddDynamic(this, &AC_SystemCharacterController::BulletEndEquip);
		}
	}
}

void AC_SystemCharacterController::CreatItemList()
{
	ShipBag->Left_Roll->ClearChildren();
	CreatBulletList();
	CreatShieldList();
}

void AC_SystemCharacterController::CreatBulletList()
{
	for (int i = 0; i < ShipState->BulletList.Num(); i++)
	{
		UC_SingleItem* newItem = CreateWidget<UC_SingleItem>(GetGameInstance(), LoadClass<UC_SingleItem>
			(nullptr, TEXT("WidgetBlueprint'/Game/UI/SolarSystemUI/BP_SingleItem.BP_SingleItem_c'")));
		newItem->Item_Name->SetText(FText::FromString(ShipState->BulletList[i].BulletClass.GetDefaultObject()->BulletName));
		newItem->Item_Pic->SetBrushFromTexture(ShipState->BulletList[i].BulletClass.GetDefaultObject()->BulletPicture);
		newItem->Item_BtnName->SetText(FText::FromString(FString::FromInt(ShipState->BulletList[i].CurrentAccout)));
		newItem->Item_Btn->SetVisibility(ESlateVisibility::Hidden);

		int temp = ShipState->BulletList[i].CurrentAccout;
		UE_LOG(LogTemp, Warning, TEXT("%d"), temp);

		newItem->BulletInfor = &ShipState->BulletList[i];
		newItem->CurrentContoller = this;

		ShipBag->Left_Roll->AddChild(newItem);

		newItem->Item_WholeBtn->SetVisibility(ESlateVisibility::Visible);
		newItem->Item_WholeBtn->OnClicked.AddDynamic(newItem, &UC_SingleItem::BindControllerItem);
	}
}
void AC_SystemCharacterController::CreatShieldList()
{
	for (int i = 0; i < ShipState->ShieldList.Num(); i++)
	{
		UC_SingleItem* newItem = CreateWidget<UC_SingleItem>(GetGameInstance(), LoadClass<UC_SingleItem>
			(nullptr, TEXT("WidgetBlueprint'/Game/UI/SolarSystemUI/BP_SingleItem.BP_SingleItem_c'")));
		
		newItem->Item_Name->SetText(FText::FromString(ShipState->ShieldList[i].ShieldClass.GetDefaultObject()->ShieldName));
		
		newItem->Item_Pic->SetBrushFromTexture(ShipState->ShieldList[i].ShieldClass.GetDefaultObject()->ShieldPicture);
		newItem->Item_BtnName->SetText(FText::FromString("1"));
		newItem->Item_Btn->SetVisibility(ESlateVisibility::Hidden);

		newItem->ShieldInfor = &ShipState->ShieldList[i];
		newItem->CurrentContoller = this;
		ShipBag->Left_Roll->AddChild(newItem);
		
		newItem->Item_WholeBtn->SetVisibility(ESlateVisibility::Visible);
		newItem->Item_WholeBtn->OnClicked.AddDynamic(newItem, &UC_SingleItem::BindControllerItem);
		
	}
}

void AC_SystemCharacterController::LoadPlayerBagState()
{
	if (ShipState)
	{
		ShipBag->HP_Bar->SetPercent(
			ShipState->PlayerCurrentHp / ShipCharacter->TotalHP);
		ShipBag->Money_Text->SetText(FText::FromString(FString::FromInt(
			ShipState->Money)));


		if (ShipState->CurrentEqipedShield && ShipState->CurrentEqipedShield->bIsEqiped == true)
		{
			ShipBag->Shield_Bar->SetPercent(
				ShipState->CurrentEqipedShield->CurrentShield / ShipState->CurrentEqipedShield->TotalShield);
		}
		else
		{
			ShipBag->Shield_Bar->SetPercent(0);
		}
	}
}

void AC_SystemCharacterController::BulletSetEquip()
{
	if (curBulletPtr)
	{
		int tempIndex = 0;
		for (; tempIndex < BAG_SIZE; tempIndex++)
		{
			if (curBulletList[tempIndex] != nullptr &&
				curBulletList[tempIndex]->BulletClass.GetDefaultObject()->BulletName ==
				curBulletPtr->BulletClass.GetDefaultObject()->BulletName)
			{
				break;
			}
			else if (curBulletList[tempIndex] == nullptr)
			{
				curBulletList[tempIndex] = curBulletPtr;
				break;
			}
		}

		if (tempIndex == BAG_SIZE)
		{
			for (int i = BAG_SIZE - 1; i > 0; i--)
			{
				curBulletList[i] = curBulletList[i - 1];
			}
			curBulletList[0] = curBulletPtr;
		}
	}
	UpdateBulletWindow();
}

void AC_SystemCharacterController::BulletEndEquip()
{
	if (curBulletPtr)
	{
		for (int i = 0; i < BAG_SIZE; i++)
		{
			if (curBulletList[i] != nullptr &&
				curBulletList[i]->BulletClass.GetDefaultObject()->BulletName 
				== curBulletPtr->BulletClass.GetDefaultObject()->BulletName)
			{
				for (int j = i; j < BAG_SIZE - 1; j++)
				{
					curBulletList[j] = curBulletList[j + 1];
				}
				curBulletList[BAG_SIZE - 1] = nullptr;
				UpdateBulletWindow();
				return;
			}
		}
	}
}

void AC_SystemCharacterController::ShieldSetEquip()
{
	if (curSheildPtr)
	{
		GenerateNewShield(curSheildPtr);
	}
}

void AC_SystemCharacterController::ShieldEndEquip()
{
	if (curSheildPtr)
	{
		if (ShipState->CurrentEqipedShield && 
			ShipState->CurrentEqipedShield->ShieldName == curSheildPtr->ShieldClass.GetDefaultObject()->ShieldName)
		{
			ShipState->CurrentEqipedShield->SetEqipState(false);
			ShipState->CurrentEqipedShield->ShieldMesh->SetVisibility(false);
		}
		else
		{
			ShipState->CurrentEqipedShield->Destroy();
			ShipState->CurrentEqipedShield = nullptr;
		}
	}
}


bool AC_SystemCharacterController::GenerateBulletList()
{
	if (ShipCharacter->BulletList.Num() == 0)
	{
		return false;
	}
	for (int i = 0; i < ShipCharacter->BulletList.Num(); i++)
	{
		FBulletBagItem tempBulletItem;
		tempBulletItem.TotalAccout = 99;
		tempBulletItem.CurrentAccout = 99;
		tempBulletItem.CurrentLoadingTime = 0;
		tempBulletItem.BulletClass = ShipCharacter->BulletList[i];
		ShipState->BulletList.Add(tempBulletItem);
	}
	return true;
}

bool AC_SystemCharacterController::GenerateShieldList()
{
	if (ShipCharacter->ShieldList.Num() == 0)
	{
		return false;
	}
	for (int i = 0; i < ShipCharacter->ShieldList.Num(); i++)
	{
		FSheildBagItem tempShieldItem;
		tempShieldItem.ShieldClass = ShipCharacter->ShieldList[i];
		ShipState->ShieldList.Add(tempShieldItem);
	}

	return true;
}

#pragma endregion

#pragma region Shop Related
void AC_SystemCharacterController::GenerateShopList(AC_NormalPlanetPawn* targetStar)
{
	targetStar->bIfCanReflesh = false;
	if (StarInfor)
	{
		StarInfor->Roll_Shop->ClearChildren();
		StarInfor->Text_Curmoney->SetText(FText::FromString(FString::FromInt(ShipState->Money)));

		for (int i = 0; i < targetStar->BulletList.Num(); i++)
		{
			if (targetStar->BulletList[i].TotalAccout > 0)
			{
				UC_ShopPage* tempPage = Cast<UC_ShopPage>(CreateWidget(GetGameInstance(), LoadClass<UC_ShopPage>
					(nullptr, TEXT("WidgetBlueprint'/Game/UI/SolarSystemUI/BP_ShopPage.BP_ShopPage_c'"))));
				if (tempPage)
				{
					tempPage->Image_Item->SetBrushFromTexture(targetStar->BulletList[i].BulletClass.GetDefaultObject()->BulletPicture);
					tempPage->Text_Name->SetText(FText::FromString(targetStar->BulletList[i].BulletClass.GetDefaultObject()->BulletName));
					tempPage->Text_Intro->SetText(FText::FromString(targetStar->BulletList[i].BulletClass.GetDefaultObject()->BulletName));
					tempPage->Text_CurPrice->SetText(FText::FromString(FString::FromInt(targetStar->BulletList[i].CurPrice)));
					tempPage->UpdateTotalCount(targetStar->BulletList[i].TotalAccout);

					tempPage->BulletInfor = &targetStar->BulletList[i];
					tempPage->tempController = this;
					StarInfor->Roll_Shop->AddChild(tempPage);
				}
			}
		}
		for (int i = 0; i < targetStar->ShieldList.Num(); i++)
		{
			if (targetStar->ShieldList[i].bIfShowOnShop == true)
			{
				UC_ShopPage* tempPage = Cast<UC_ShopPage>(CreateWidget(GetGameInstance(), LoadClass<UC_ShopPage>
					(nullptr, TEXT("WidgetBlueprint'/Game/UI/SolarSystemUI/BP_ShopPage.BP_ShopPage_c'"))));
				if (tempPage)
				{
					tempPage->Image_Item->SetBrushFromTexture(targetStar->ShieldList[i].ShieldClass.GetDefaultObject()->ShieldPicture);
					tempPage->Text_Name->SetText(FText::FromString(targetStar->ShieldList[i].ShieldClass.GetDefaultObject()->ShieldName));
					tempPage->Text_Intro->SetText(FText::FromString(targetStar->ShieldList[i].ShieldClass.GetDefaultObject()->ShieldName));
					tempPage->Text_CurPrice->SetText(FText::FromString(FString::FromInt(targetStar->ShieldList[i].CurPrice)));
					tempPage->UpdateTotalCount(1);

					tempPage->ShieldInfor = &targetStar->ShieldList[i];
					tempPage->tempController = this;
					StarInfor->Roll_Shop->AddChild(tempPage);
				}
			}
		}
	}
}

void AC_SystemCharacterController::ResetStarShop(AC_NormalPlanetPawn* targetStar)
{
	targetStar->bIfCanReflesh = true;
	if (StarInfor)
	{
		StarInfor->Roll_Shop->ClearChildren();
	}
}

bool AC_SystemCharacterController::BuySomeItem(FSheildBagItem* shieldItem)
{
	if (ShipState)
	{
		if (ShipState->Money < shieldItem->CurPrice)
		{
			return false;
		}
		else if (ShipState->AddItem(shieldItem))
		{
			ShipState->Money -= shieldItem->CurPrice;
			StarInfor->Text_Curmoney->SetText(FText::FromString(FString::FromInt(ShipState->Money)));

			return true;
		}
	}
	return false;
}

bool AC_SystemCharacterController::BuySomeItem(FBulletBagItem* bulletItem)
{
	if (ShipState)
	{
		if (ShipState->Money < bulletItem->CurPrice * bulletItem->CurrentAccout)
		{
			return false;
		}
		else if (ShipState->AddItem(bulletItem))
		{
			ShipState->Money -= bulletItem->CurPrice * bulletItem->CurrentAccout;
			StarInfor->Text_Curmoney->SetText(FText::FromString(FString::FromInt(ShipState->Money)));

			return true;
		}
	}
	return false;
}

bool AC_SystemCharacterController::GetMoney(int moneyCount, bool addOrSub)
{
	if (ShipState)
	{
		if (addOrSub)
		{
			ShipState->Money += moneyCount;
			return true;
		}
		else
		{
			if (ShipState->Money < moneyCount)
			{
				return false;
			}
			else
			{
				ShipState->Money -= moneyCount;
				return true;
			}
		}
	}
	return false;
}

#pragma endregion