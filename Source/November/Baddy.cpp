// Fill out your copyright notice in the Description page of Project Settings.

#include "November.h"
#include "Baddy.h"

#include "GameStats.h"


// Sets default values
ABaddy::ABaddy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    m_pBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
    m_pBox->SetCollisionProfileName(TEXT("OverlapAll"));

    m_pMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    m_pMesh->SetCollisionProfileName(TEXT("NoCollision"));

    RootComponent = m_pBox;
    m_pMesh->AttachTo(RootComponent);

    m_nHealth = 1;
    m_vPosition = FVector::ZeroVector;
    m_vVelocity = FVector::ZeroVector;
}

// Called when the game starts or when spawned
void ABaddy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaddy::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

    if (m_vPosition.X < -500.0f)
    {
        Destroy();
    }

    m_vPosition += m_vVelocity * DeltaTime;
    SetActorLocation(m_vPosition);

}


void ABaddy::Damage(int nDamage)
{
    m_nHealth -= nDamage;
    if (m_nHealth <= 0)
    {
        // Increase score and destroy actor
        AGameStats::Score += 100;
        AGameStats::Update = 1;
        Destroy();
    }
}
