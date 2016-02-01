// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Torus.generated.h"

//*******
// This actor is used as the rotating background 
// in the game.
//*******

UCLASS()
class NOVEMBER_API ATorus : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATorus();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere)
    UStaticMeshComponent* m_pMesh;

    float m_fRotation;
	
};
