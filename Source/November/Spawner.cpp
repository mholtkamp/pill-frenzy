// Fill out your copyright notice in the Description page of Project Settings.

#include "November.h"
#include "Spawner.h"
#include "GameStats.h"

#include "Antibody.h"
#include "Bacteriophage.h"
#include "Spike.h"
#include "WhiteCell.h"

#define WAVE_1_TIME 20.0f
#define WAVE_2_TIME 60.0f
#define WAVE_3_TIME 100.0f
#define WAVE_4_TIME 140.0f
#define WAVE_5_TIME 180.0f

#define GAME_END_TIME 110.0f

#define WAVE_1_SPAWN_TIME 3.0f
#define WAVE_2_SPAWN_TIME 2.0f
#define WAVE_3_SPAWN_TIME 1.0f
#define WAVE_4_SPAWN_TIME 2.5f
#define WAVE_5_SPAWN_TIME 2.0f


#define ANTIBODY_RATE_1 0.60f
#define SPIKE_RATE_1 0.68f
#define WHITECELL_RATE_1 0.80f
#define BACTERIOPHAGE_RATE_1 1.0f

#define ANTIBODY_RATE_2 0.4f
#define SPIKE_RATE_2 0.52f
#define WHITECELL_RATE_2 0.85f
#define BACTERIOPHAGE_RATE_2 1.0f

#define ANTIBODY_RATE_3 0.2f
#define SPIKE_RATE_3 0.4f
#define WHITECELL_RATE_3 0.9f
#define BACTERIOPHAGE_RATE_3 1.0f

#define ANTIBODY_RATE_4 0.2f
#define SPIKE_RATE_4 0.35f
#define WHITECELL_RATE_4 0.80f
#define BACTERIOPHAGE_RATE_4 1.0f

#define ANTIBODY_RATE_5 0.25f
#define SPIKE_RATE_5 0.5f
#define WHITECELL_RATE_5 0.75f
#define BACTERIOPHAGE_RATE_5 1.0f



// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    m_fTime = 0.0f;
    m_nWave = 1;
    m_nActive = 1;
    m_fSpawnTime = 0.0f;
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();

    m_fTime = 0.0f;
    m_nWave = 1;
    m_nActive = 1;
    m_fSpawnTime = 0.0f;
}

// Called every frame
void ASpawner::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

    m_fSpawnTime += DeltaTime;
    m_fTime += DeltaTime;

    if (m_nWave == 1 &&
        m_fTime >= WAVE_1_TIME)
    {
        m_nWave = 2;
        AGameStats::Wave = m_nWave;
        AGameStats::Update = 1;
    }
    else if (m_nWave == 2 &&
             m_fTime >= WAVE_2_TIME)
    {
        m_nWave = 3;
        AGameStats::Wave = m_nWave;
        AGameStats::Update = 1;
    }
    else if (m_nWave == 3 &&
             m_fTime >= WAVE_3_TIME)
    {
        m_nActive = 0;
    }


    // Check time and spawn baddies!
    if (m_nActive != 0)
    {
        Spawn();
    }
    else
    {
        if( m_fTime >= GAME_END_TIME)
        {
            UGameplayStatics::OpenLevel(this, TEXT("WinLevel"));
        }
    }
}

void ASpawner::Spawn()
{
    switch(m_nWave)
    {
    case 1:
        Spawn1();
        break;
    case 2:
        Spawn2();
        break;
    case 3:
        Spawn3();
        break;
    case 4:
        Spawn4();
        break;
    case 5:
        Spawn5();
        break;
    default:
        break;
    }
}

void ASpawner::Spawn1()
{
    float fRoll = FMath::FRand();
    FVector vLoc(3000.0f, 0.0f, 0.0f);

    if (m_fSpawnTime >= WAVE_1_SPAWN_TIME)
    {
        if (fRoll <= ANTIBODY_RATE_1)
        {
            GetWorld()->SpawnActor<AAntibody>(vLoc, FRotator::ZeroRotator);
        }
        else if (fRoll <= SPIKE_RATE_1)
        {
            GetWorld()->SpawnActor<ASpike>(vLoc, FRotator::ZeroRotator);
        }
        else if (fRoll <= WHITECELL_RATE_1)
        {
            GetWorld()->SpawnActor<AWhiteCell>(vLoc, FRotator::ZeroRotator);
        }
        else if (fRoll <= BACTERIOPHAGE_RATE_1)
        {
            GetWorld()->SpawnActor<ABacteriophage>(vLoc, FRotator::ZeroRotator);
        }

        m_fSpawnTime = 0.0f;
    }
}

void ASpawner::Spawn2()
{
    float fRoll = FMath::FRand();
    FVector vLoc(3000.0f, 0.0f, 0.0f);

    if (m_fSpawnTime >= WAVE_2_SPAWN_TIME)
    {
        if (fRoll <= ANTIBODY_RATE_2)
        {
            GetWorld()->SpawnActor<AAntibody>(vLoc, FRotator::ZeroRotator);
        }
        else if (fRoll <= SPIKE_RATE_2)
        {
            GetWorld()->SpawnActor<ASpike>(vLoc, FRotator::ZeroRotator);
        }
        else if (fRoll <= WHITECELL_RATE_2)
        {
            GetWorld()->SpawnActor<AWhiteCell>(vLoc, FRotator::ZeroRotator);
        }
        else if (fRoll <= BACTERIOPHAGE_RATE_2)
        {
            GetWorld()->SpawnActor<ABacteriophage>(vLoc, FRotator::ZeroRotator);
        }

        m_fSpawnTime = 0.0f;
    }
}

void ASpawner::Spawn3()
{
    float fRoll = FMath::FRand();
    FVector vLoc(3000.0f, 0.0f, 0.0f);

    if (m_fSpawnTime >= WAVE_3_SPAWN_TIME)
    {
        if (fRoll <= ANTIBODY_RATE_3)
        {
            GetWorld()->SpawnActor<AAntibody>(vLoc, FRotator::ZeroRotator);
        }
        else if (fRoll <= SPIKE_RATE_3)
        {
            GetWorld()->SpawnActor<ASpike>(vLoc, FRotator::ZeroRotator);
        }
        else if (fRoll <= WHITECELL_RATE_3)
        {
            GetWorld()->SpawnActor<AWhiteCell>(vLoc, FRotator::ZeroRotator);
        }
        else if (fRoll <= BACTERIOPHAGE_RATE_3)
        {
            GetWorld()->SpawnActor<ABacteriophage>(vLoc, FRotator::ZeroRotator);
        }

        m_fSpawnTime = 0.0f;
    }
}

void ASpawner::Spawn4()
{
    float fRoll = FMath::FRand();
    FVector vLoc(3000.0f, 0.0f, 0.0f);

    if (m_fSpawnTime >= WAVE_4_SPAWN_TIME)
    {
        if (fRoll <= ANTIBODY_RATE_4)
        {
            GetWorld()->SpawnActor<AAntibody>(vLoc, FRotator::ZeroRotator);
        }
        if (fRoll <= SPIKE_RATE_4)
        {
            GetWorld()->SpawnActor<ASpike>(vLoc, FRotator::ZeroRotator);
        }
        if (fRoll <= WHITECELL_RATE_4)
        {
            GetWorld()->SpawnActor<AWhiteCell>(vLoc, FRotator::ZeroRotator);
        }
        if (fRoll <= BACTERIOPHAGE_RATE_4)
        {
            GetWorld()->SpawnActor<ABacteriophage>(vLoc, FRotator::ZeroRotator);
        }

        m_fSpawnTime = 0.0f;
    }
}

void ASpawner::Spawn5()
{
    float fRoll = FMath::FRand();
    FVector vLoc(3000.0f, 0.0f, 0.0f);

    if (m_fSpawnTime >= WAVE_5_SPAWN_TIME)
    {
        if (fRoll <= ANTIBODY_RATE_5)
        {
            GetWorld()->SpawnActor<AAntibody>(vLoc, FRotator::ZeroRotator);
        }
        if (fRoll <= SPIKE_RATE_5)
        {
            GetWorld()->SpawnActor<ASpike>(vLoc, FRotator::ZeroRotator);
        }
        if (fRoll <= WHITECELL_RATE_5)
        {
            GetWorld()->SpawnActor<AWhiteCell>(vLoc, FRotator::ZeroRotator);
        }
        if (fRoll <= BACTERIOPHAGE_RATE_5)
        {
            GetWorld()->SpawnActor<ABacteriophage>(vLoc, FRotator::ZeroRotator);
        }

        m_fSpawnTime = 0.0f;
    }
}
