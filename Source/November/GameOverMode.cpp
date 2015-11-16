// Fill out your copyright notice in the Description page of Project Settings.

#include "November.h"
#include "GameOverMode.h"
#include "GameOverPawn.h"

AGameOverMode::AGameOverMode()
{
    DefaultPawnClass = AGameOverPawn::StaticClass();
}
