// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Baddy.generated.h"

UCLASS()
class NOVEMBER_API ABaddy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaddy();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

    void Damage(int nDamage);

    UPROPERTY(EditAnywhere)
    UBoxComponent* m_pBox;

	UPROPERTY(EditAnywhere)
    UStaticMeshComponent* m_pMesh;

    UPROPERTY(EditAnywhere)
    int32 m_nHealth;

    UPROPERTY(EditAnywhere)
    FVector m_vPosition;

    UPROPERTY(EditAnywhere)
    FVector m_vVelocity;
	
};
