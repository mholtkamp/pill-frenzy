// Fill out your copyright notice in the Description page of Project Settings.

#include "November.h"
#include "Pill.h"
#include "Baddy.h"

#define PILL_DAMAGE 1

static UParticleSystem* s_pParticleSys = 0;
static USoundWave*      s_pSound       = 0;

APill::APill()
{
    // Find asset references using static variables.
    static ConstructorHelpers::FObjectFinder<UStaticMesh> ofMesh(TEXT("StaticMesh'/Game/StaticMeshes/pill.pill'"));
    static ConstructorHelpers::FObjectFinder<UParticleSystem> ofSparks(TEXT("ParticleSystem'/Game/ParticleSystems/P_Sparks.P_Sparks'"));
    static ConstructorHelpers::FObjectFinder<USoundWave> ofSound(TEXT("SoundWave'/Game/Sounds/PillHit.PillHit'"));

    // Set up box extents for collisions
    m_pBox->InitBoxExtent(FVector(9.0f, 5.0f, 5.0f));
    
    if (ofMesh.Succeeded()   &&
        ofSparks.Succeeded() &&
        ofSound.Succeeded())
    {
        m_pMesh->SetStaticMesh(ofMesh.Object);
        m_pMesh->SetWorldScale3D(FVector(0.15f, 0.15f, 0.15f));
        s_pParticleSys = ofSparks.Object;
        s_pSound       = ofSound.Object;
    }
    
    RootComponent = m_pBox;
    m_pMesh->AttachTo(RootComponent);

    // Scale actor to the preferred size
    SetActorScale3D(FVector(0.6f, 0.6f, 0.6f));

    // Set delegates for collision
    OnActorBeginOverlap.AddDynamic(this, &APill::OnOverlapBegin);
}

void APill::OnOverlapBegin(AActor* pOther)
{
    if (IsPendingKill()      == 0 &&
        Cast<ABaddy>(pOther) != 0 &&
        m_bCollisionActive   == true)
    {
        Cast<ABaddy>(pOther)->Damage(PILL_DAMAGE);
        UGameplayStatics::SpawnEmitterAtLocation(this, s_pParticleSys, GetActorLocation());
        UGameplayStatics::PlaySoundAtLocation(this, s_pSound, GetActorLocation());
        Destroy();
    }
}


