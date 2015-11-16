// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Baddy.h"
#include "WhiteCell.generated.h"

/**
 * 
 */
UCLASS()
class NOVEMBER_API AWhiteCell : public ABaddy
{
	GENERATED_BODY()
	
	AWhiteCell();

    // Called when the game starts or when spawned
	virtual void BeginPlay() override;

    // Called every frame
	virtual void Tick( float DeltaTime ) override;

    float m_fBurstTime;

    float m_fTime;

    float m_fRotation;

};
