// Fill out your copyright notice in the Description page of Project Settings.

#include "November.h"
#include "Blob.h"
#include "Submarine.h"

#define BLOB_DAMAGE 1

static UParticleSystem* s_pParticleSys = 0;
static USoundWave* s_pSound;

ABlob::ABlob()
{
    static ConstructorHelpers::FObjectFinder<UStaticMesh> ofMesh(TEXT("StaticMesh'/Game/StaticMeshes/blob.blob'"));
    static ConstructorHelpers::FObjectFinder<UParticleSystem> ofSparks(TEXT("ParticleSystem'/Game/ParticleSystems/P_SparksBlob.P_SparksBlob'"));
    static ConstructorHelpers::FObjectFinder<USoundWave> ofSound(TEXT("SoundWave'/Game/Sounds/BlobHit.BlobHit'"));

    m_pBox->InitBoxExtent(FVector(6.0f, 6.0f, 6.0f));

    m_pBox->SetCollisionProfileName(TEXT("OverlapAll"));
    
    if (ofMesh.Succeeded() &&
        ofSparks.Succeeded() &&
        ofSound.Succeeded())
    {
        m_pMesh->SetStaticMesh(ofMesh.Object);
        m_pMesh->SetWorldScale3D(FVector(0.385f, 0.385f, 0.385f));
        s_pParticleSys = ofSparks.Object;
        s_pSound = ofSound.Object;
    }
    
    RootComponent = m_pBox;
    m_pMesh->AttachTo(RootComponent);

    SetActorScale3D(FVector(0.6f, 0.6f, 0.6f));

    // Set delegates for collision
    OnActorBeginOverlap.AddDynamic(this, &ABlob::OnOverlapBegin);
}

void ABlob::OnOverlapBegin(AActor* pOther)
{
    if (IsPendingKill() == 0 &&
        Cast<ASubmarine>(pOther) != 0)
    {
        Cast<ASubmarine>(pOther)->Damage(BLOB_DAMAGE);
        UGameplayStatics::SpawnEmitterAtLocation(this, s_pParticleSys, GetActorLocation());
        UGameplayStatics::PlaySoundAtLocation(this, s_pSound, GetActorLocation());
        Destroy();
    }
}


