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

    // Variable to keep track of next bullet fire
    float m_fFireTime;

    // Keeps track of time since last fire
    float m_fTime;
	
    // Angular rotation of antibody
    float m_fRotation;
	
};
