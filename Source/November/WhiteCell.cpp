// Fill out your copyright notice in the Description page of Project Settings.

#include "November.h"
#include "WhiteCell.h"


#include "Blob.h"

#define BADDY_SPAWN_X 475.0f
#define DEFAULT_HEALTH 5
#define TOP_Z 130.0f
#define BOT_Z -130.0f
#define MIN_VEL -100.0f
#define MAX_VEL -40.0f
#define MIN_BURST_TIME 1.0f
#define MAX_BURST_TIME 4.0f
#define ROT_SPEED 50.0f
#define BLOB_VEL 200.0f

AWhiteCell::AWhiteCell()
{
    m_pBox->InitBoxExtent(FVector(29.0f, 29.0f, 29.0f));

    // Get assets
    static ConstructorHelpers::FObjectFinder<UStaticMesh> ofMesh(TEXT("StaticMesh'/Game/StaticMeshes/white_cell.white_cell'"));
    
    if (ofMesh.Succeeded())
    {
        m_pMesh->SetStaticMesh(ofMesh.Object);
        m_pMesh->SetWorldScale3D(FVector(0.4f,0.4f,0.4f));
    }

    SetActorScale3D(FVector(0.7f,0.7f,0.7f));

    // Initialize instance variables
    m_fBurstTime = MAX_BURST_TIME;
    m_fTime = 0.0f;
    m_nHealth = 5;
    m_fRotation = 0.0f;
}

void AWhiteCell::BeginPlay()
{
    Super::BeginPlay();

    // Set position and speed
    float fZRoll = FMath::FRand() * (TOP_Z - BOT_Z) + BOT_Z;
    m_vPosition = FVector(BADDY_SPAWN_X, 0.0f, fZRoll);

    float fXVelRoll = FMath::FRand() * (MAX_VEL - MIN_VEL) + MIN_VEL;
    m_vVelocity = FVector(fXVelRoll, 0.0f, 0.0f);

    // Time between each burst of blobs
    m_fBurstTime = FMath::FRand() * (MAX_BURST_TIME - MIN_BURST_TIME) + MIN_BURST_TIME;
}

// Called every frame
void AWhiteCell::Tick( float DeltaTime )
{
    Super::Tick(DeltaTime);

    m_fTime += DeltaTime;

    m_fRotation += ROT_SPEED * DeltaTime;
    SetActorRotation(FRotator(0.0f, m_fRotation, 0.0f));

    if (m_fTime >= m_fBurstTime)
    {
        ABlob* pBlob = 0;

        float fLowestAngle = 210.0f - FMath::FRand() * 30.0f;
        float fSpreadAngle = 10.0f + FMath::FRand() * 10.0f;

        // Fire five blobs!
        for (int32 i = 0; i < 5; i++)
        {
            pBlob = GetWorld()->SpawnActor<ABlob>();
            FVector vSpeed(FMath::Cos(FMath::DegreesToRadians(fLowestAngle - fSpreadAngle*i)) * BLOB_VEL,
                           0.0f,
                           FMath::Sin(FMath::DegreesToRadians(fLowestAngle - fSpreadAngle*i)) * BLOB_VEL);

            pBlob->Fire(m_vPosition,
                        vSpeed);
        }

        m_fTime = 0.0f;
    }
}


