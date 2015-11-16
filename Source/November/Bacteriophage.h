// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Baddy.h"
#include "Bacteriophage.generated.h"

/**
 * 
 */
UCLASS()
class NOVEMBER_API ABacteriophage : public ABaddy
{
	GENERATED_BODY()
	
	ABacteriophage();

    // Called when the game starts or when spawned
	virtual void BeginPlay() override;

    // Called every frame
	virtual void Tick( float DeltaTime ) override;

    UPROPERTY(EditAnywhere)
    USkeletalMeshComponent* m_pSkeletalMesh;

    float m_fDropX;

    int m_nDropped;
	
	
};
