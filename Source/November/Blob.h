// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Bullet.h"
#include "Blob.generated.h"

/**
 * 
 */
UCLASS()
class NOVEMBER_API ABlob : public ABullet
{
	GENERATED_BODY()
	
	ABlob();

    // Overlap delegate function
    UFUNCTION()
    void OnOverlapBegin(AActor* pOther);
	
	
};
