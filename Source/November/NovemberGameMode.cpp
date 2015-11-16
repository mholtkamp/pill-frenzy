// Fill out your copyright notice in the Description page of Project Settings.

#include "November.h"
#include "NovemberGameMode.h"
#include "Submarine.h"

ANovemberGameMode::ANovemberGameMode()
{
    DefaultPawnClass = ASubmarine::StaticClass();
}
