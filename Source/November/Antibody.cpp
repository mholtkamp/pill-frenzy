// Fill out your copyright notice in the Description page of Project Settings.

#include "November.h"
#include "Antibody.h"


#include "Blob.h"

#define BADDY_SPAWN_X 475.0f

#define DEFAULT_HEALTH 5

#define TOP_Z 130.0f
#define BOT_Z -130.0f

#define MIN_VEL -100.0f
#define MAX_VEL -40.0f

#define MIN_FIRE_TIME 0.2f
#define MAX_FIRE_TIME 4.0f

#define BLOB_VEL -270.0f

#define ROT_SPEED 200.0f

AAntibody::AAntibody()
{
    m_pBox->InitBoxExtent(FVector(17.0f, 4.0f, 12.0f));

    static ConstructorHelpers::FObjectFinder<UStaticMesh> ofMesh(TEXT("StaticMesh'/Game/StaticMeshes/antibody.antibody'"));
    
    if (ofMesh.Succeeded())
    {
        m_pMesh->SetStaticMesh(ofMesh.Object);
        m_pMesh->SetWorldScale3D(FVector(0.38f,0.38f,0.38f));
    }

    //SetActorScale3D(FVector(0.7f,0.7f,0.7f));

    m_fFireTime = MIN_FIRE_TIME;
    m_fTime = 0.0f;
    m_nHealth = 3;
    m_fRotation = 0.0f;

}

void AAntibody::BeginPlay()
{
    Super::BeginPlay();

    // Set position and speed
    float fZRoll = FMath::FRand() * (TOP_Z - BOT_Z) + BOT_Z;
    m_vPosition = FVector(BADDY_SPAWN_X, 0.0f, fZRoll);

    float fXVelRoll = FMath::FRand() * (MAX_VEL - MIN_VEL) + MIN_VEL;
    m_vVelocity = FVector(fXVelRoll, 0.0f, 0.0f);

    m_fFireTime = FMath::FRand() * (MAX_FIRE_TIME - MIN_FIRE_TIME) + MIN_FIRE_TIME;
}

// Called every frame
void AAntibody::Tick( float DeltaTime )
{
    Super::Tick(DeltaTime);

    m_fTime += DeltaTime;

    m_fRotation += DeltaTime * ROT_SPEED;
    SetActorRotation(FRotator(0.0f, 0.0f, m_fRotation));

    if (m_fTime >= m_fFireTime)
    {
        ABlob* pBlob = GetWorld()->SpawnActor<ABlob>();
        
        if (pBlob != 0)
        {
            pBlob->Fire(m_vPosition,
                        FVector(BLOB_VEL, 0.0f, 0.0f));
        }

        m_fFireTime = FMath::FRand() * (MAX_FIRE_TIME - MIN_FIRE_TIME) + MIN_FIRE_TIME;
        m_fTime = 0.0f;
    }

}



