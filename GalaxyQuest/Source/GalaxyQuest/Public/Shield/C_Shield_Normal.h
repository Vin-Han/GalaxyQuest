// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Shield/C_Shield_Base.h"
#include "C_Shield_Normal.generated.h"

/**
 * 
 */
UCLASS()
class GALAXYQUEST_API AC_Shield_Normal : public AC_Shield_Base
{
	GENERATED_BODY()

public:
    virtual void Tick(float DeltaTime) override;
};
