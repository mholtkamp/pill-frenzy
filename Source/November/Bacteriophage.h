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

    // Skeletal mesh component
    UPROPERTY(EditAnywhere)
    USkeletalMeshComponent* m_pSkeletalMesh;

    // Location on x axis to drop a blob
    float m_fDropX;

    // Boolean flag to identify whether blob has been dropped
    int m_nDropped;
	
	
};
