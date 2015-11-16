// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class NOVEMBER_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

    virtual void Fire (FVector vPosition,
                       FVector vVelocity);

    UPROPERTY(EditAnywhere)
    UBoxComponent* m_pBox;

	UPROPERTY(EditAnywhere)
    UStaticMeshComponent* m_pMesh;

    UPROPERTY(EditAnywhere)
    FVector m_vPosition;

    UPROPERTY(EditAnywhere)
    FVector m_vVelocity;
	
};
