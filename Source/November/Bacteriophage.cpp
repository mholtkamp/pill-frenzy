// Fill out your copyright notice in the Description page of Project Settings.

#include "November.h"
#include "Bacteriophage.h"
#include "Blob.h"

#define BADDY_SPAWN_X 475.0f
#define DEFAULT_HEALTH 5
#define TOP_Z 130.0f
#define BOT_Z 100.0f
#define MIN_VEL -300.0f
#define MAX_VEL -200.0f
#define MIN_DROP -255.0f
#define MAX_DROP -120.0f
#define DROP_VEL -200.0f

// A static pointer to the animation asset
static UAnimSequence* s_pAnim = 0;

ABacteriophage::ABacteriophage()
{
    static ConstructorHelpers::FObjectFinder<USkeletalMesh> ofSkeletalMesh(TEXT("SkeletalMesh'/Game/SkeletalMesh/bacteriophage.bacteriophage'"));
    static ConstructorHelpers::FObjectFinder<UAnimSequence> ofAnim(TEXT("AnimSequence'/Game/SkeletalMesh/bacteriophage_Anim.bacteriophage_Anim'"));

    // initialize bounding box
    m_pBox->InitBoxExtent(FVector(10.0f, 10.0f, 28.0f));

    m_pSkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skele Mesh"));
    m_pSkeletalMesh->SetCollisionProfileName(TEXT("NoCollision"));

    if (ofSkeletalMesh.Succeeded() &&
        ofAnim.Succeeded())
    {
        m_pSkeletalMesh->SetSkeletalMesh(ofSkeletalMesh.Object);

        // Save the animation object to static variable so it can
        // be used later on beginplay
        s_pAnim = ofAnim.Object;
    }

    // Attach to root component (BoxComponent)
    m_pSkeletalMesh->AttachTo(RootComponent);

    // Initialize instance variables
    m_fDropX = 0.0f;
    m_nDropped = 0;
    m_nHealth = 5;
}

void ABacteriophage::BeginPlay()
{
    Super::BeginPlay();

    // Setup Animation
    m_pSkeletalMesh->SetAnimation(s_pAnim);
    m_pSkeletalMesh->PlayAnimation(s_pAnim, 1);

    // Set position and speed
    float fZRoll = FMath::FRand() * (TOP_Z - BOT_Z) + BOT_Z;
    m_vPosition = FVector(BADDY_SPAWN_X, 0.0f, fZRoll);

    float fXVelRoll = FMath::FRand() * (MAX_VEL - MIN_VEL) + MIN_VEL;
    m_vVelocity = FVector(fXVelRoll, 0.0f, 0.0f);

    // Randomly determine drop location along x axis
    m_fDropX = FMath::FRand() * (MAX_DROP - MIN_DROP) + MIN_DROP;
}

// Called every frame
void ABacteriophage::Tick( float DeltaTime )
{
    Super::Tick(DeltaTime);

    // If bacteriophage is past its drop position...
    // And it hasn't dropped a blob yet...
    if (m_nDropped    == 0 &&
        m_vPosition.X < m_fDropX)
    {
        // Drop the blob
        ABlob* pBlob = GetWorld()->SpawnActor<ABlob>();
        pBlob->Fire(m_vPosition, FVector(0.0f, 0.0f, DROP_VEL));
        m_nDropped = 1;
    }
}
