// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Baddy.h"
#include "Antibody.generated.h"

/**
 * 
 */
UCLASS()
class NOVEMBER_API AAntibody : public ABaddy
{
	GENERATED_BODY()
	
	AAntibody();

    // Called when the game starts or when spawned
	virtual void BeginPlay() override;

    // Called every frame
	virtual void Tick( float DeltaTime ) override;

    float m_fFireTime;

    float m_fTime;
	
    float m_fRotation;
	
};
