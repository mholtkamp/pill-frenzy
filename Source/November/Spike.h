// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Baddy.h"
#include "Spike.generated.h"

/**
 * 
 */
UCLASS()
class NOVEMBER_API ASpike : public ABaddy
{
	GENERATED_BODY()
	
	ASpike();

    // Called when the game starts or when spawned
	virtual void BeginPlay() override;

    // Called every frame
	virtual void Tick( float DeltaTime ) override;

    UFUNCTION()
    void OnOverlapBegin(AActor* pOther);

    void Bounce(); 

    int32 m_nDir;

    float m_fSpeed;

    float m_fRotation;

    int32 m_nHit;

};
