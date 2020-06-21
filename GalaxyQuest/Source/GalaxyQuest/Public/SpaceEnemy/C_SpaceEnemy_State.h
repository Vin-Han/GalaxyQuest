// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "C_SpaceEnemy_State.generated.h"

UENUM(BluePrintType)
enum class EnemyState :uint8{
    AROUND = 0 UMETA(Displayname = "Around"),
    TRACK = 1 UMETA(Displayname = "Track"),
    PATROL = 2 UMETA(Displayname = "Patrol"),
    RETURN = 3 UMETA(Displayname = "Return")
};
