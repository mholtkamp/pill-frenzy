// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Bullet.h"
#include "Pill.generated.h"

/**
 * 
 */
UCLASS()
class NOVEMBER_API APill : public ABullet
{
	GENERATED_BODY()
	
	APill();

    UFUNCTION()
    void OnOverlapBegin(AActor* pOther);
	
};
