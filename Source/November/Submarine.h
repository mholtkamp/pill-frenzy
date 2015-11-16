// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Submarine.generated.h"

UCLASS()
class NOVEMBER_API ASubmarine : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASubmarine();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

    void MoveX(float fAxisValue);

    void MoveZ(float fAxisValue);

    void Fire();

    void Damage(int nDamage);

    UPROPERTY(EditAnywhere)
    UBoxComponent* m_pBox;

    UPROPERTY(EditAnywhere)
    UStaticMeshComponent* m_pSubMesh;

    UPROPERTY(EditAnywhere)
    UStaticMeshComponent* m_pAxleMesh;

    UPROPERTY(EditAnywhere)
    UStaticMeshComponent* m_pPropellerMesh;

    UPROPERTY(EditAnywhere)
    USpotLightComponent* m_pSideSpotlight;

    UPROPERTY(EditAnywhere)
    UPointLightComponent* m_pPointlight;

    UPROPERTY(EditAnywhere)
    USpotLightComponent* m_pDirectSpotlight;

    UPROPERTY(EditAnywhere)
    UParticleSystemComponent* m_pBubbles;

    FVector m_vMoveDir;

    UPROPERTY(EditAnywhere)
    float m_fSpeed;

    UPROPERTY(EditAnywhere)
    float m_fPropRotSpeed;

    float m_fPropRot;

    UPROPERTY(EditAnywhere)
    int32 m_nHealth;
	
};
