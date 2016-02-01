// Fill out your copyright notice in the Description page of Project Settings.

#include "November.h"
#include "Spike.h"
#include "Submarine.h"

#define BADDY_SPAWN_X 475.0f
#define DEFAULT_HEALTH 999
#define TOP_Z 130.0f
#define BOT_Z -130.0f
#define MIN_SPEED 100.0f
#define MAX_SPEED 400.0f
#define ROT_SPEED 50.0f
#define MAX_ANGLE 60.0f
#define MIN_ANGLE 20.0f
#define ROT_SPEED 180.0f
#define SPIKE_DAMAGE 2

static UParticleSystem* s_pParticleSys;
static USoundWave* s_pSound;

ASpike::ASpike()
{
    m_pBox->InitBoxExtent(FVector(29.0f, 29.0f, 29.0f));

    static ConstructorHelpers::FObjectFinder<UStaticMesh> ofMesh(TEXT("StaticMesh'/Game/StaticMeshes/spike.spike'"));
    static ConstructorHelpers::FObjectFinder<UParticleSystem> ofSparks(TEXT("ParticleSystem'/Game/ParticleSystems/P_SparksBlob.P_SparksBlob'"));
    static ConstructorHelpers::FObjectFinder<USoundWave> ofSound(TEXT("SoundWave'/Game/Sounds/BlobHit.BlobHit'"));
    
    if (ofMesh.Succeeded()   && 
        ofSparks.Succeeded() &&
        ofSound.Succeeded())
    {
        m_pMesh->SetStaticMesh(ofMesh.Object);
        m_pMesh->SetWorldScale3D(FVector(0.4f,0.4f,0.4f));
        s_pParticleSys = ofSparks.Object;
        s_pSound = ofSound.Object;
    }

    SetActorScale3D(FVector(0.62f,0.62f,0.62f));
    SetActorRotation(FRotator(0.0f, 90.0f, 0.0f));

    // Set delegates for collision
    OnActorBeginOverlap.AddDynamic(this, &ASpike::OnOverlapBegin);

    m_nHealth   = DEFAULT_HEALTH;
    m_nDir      = 0;
    m_fSpeed    = MIN_SPEED;
    m_fRotation = 0.0f;
    m_nHit      = 0;
}

void ASpike::BeginPlay()
{
    Super::BeginPlay();
    
    m_nDir   = FMath::Round(FMath::FRand());
    m_fSpeed = FMath::FRand() * (MAX_SPEED - MIN_SPEED) + MIN_SPEED;

    // Set position and speed
    float fZRoll = FMath::FRand() * (TOP_Z - BOT_Z) + BOT_Z;
    m_vPosition = FVector(BADDY_SPAWN_X, 0.0f, fZRoll);

    Bounce();

}

// Called every frame
void ASpike::Tick( float DeltaTime )
{
    Super::Tick(DeltaTime);

    m_fRotation += DeltaTime * ROT_SPEED;
    SetActorRotation(FRotator(0.0f, 90.0f, m_fRotation));

    if (m_vPosition.Z >= TOP_Z && 
        m_nDir        != 0)
    {
        Bounce();
    }
    else if (m_vPosition.Z <= BOT_Z && 
             m_nDir        == 0)
    {
        Bounce();
    }

}

void ASpike::Bounce()
{
    m_nDir = !m_nDir;

    float fAngle = 0.0f;

    if (m_nDir == 0)
    {
        fAngle = 270.0f - (FMath::FRand() * (MAX_ANGLE - MIN_ANGLE) + MIN_ANGLE);
    }
    else
    {
         fAngle = 90.0f + (FMath::FRand() * (MAX_ANGLE - MIN_ANGLE) + MIN_ANGLE);
    }

    m_vVelocity.Set(FMath::Cos(FMath::DegreesToRadians(fAngle))* m_fSpeed,
                    0.0f,
                    FMath::Sin(FMath::DegreesToRadians(fAngle))* m_fSpeed);
}

void ASpike::OnOverlapBegin(AActor* pOther)
{
    if (m_nHit                   == 0 &&
        Cast<ASubmarine>(pOther) != 0)
    {
        Cast<ASubmarine>(pOther)->Damage(SPIKE_DAMAGE);
        UGameplayStatics::SpawnEmitterAtLocation(this, s_pParticleSys, GetActorLocation());
        UGameplayStatics::PlaySoundAtLocation(this, s_pSound, GetActorLocation());
        m_nHit = 1;
    }
}
