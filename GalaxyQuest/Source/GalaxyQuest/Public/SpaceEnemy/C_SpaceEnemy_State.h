// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "C_SpaceEnemy_State.generated.h"

UENUM(BluePrintType)
enum class EnemyState :uint8{
    AROUND UMETA(Displayname = "Around"),
    TRACK UMETA(Displayname = "Track"),
    PATROL UMETA(Displayname = "Patrol")
};
