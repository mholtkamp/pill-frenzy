// Fill out your copyright notice in the Description page of Project Settings.

#include "November.h"
#include "Bullet.h"

#define KILL_RADIUS 2000.0f

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    m_pMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    m_pBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));

    m_pBox->SetCollisionProfileName(TEXT("OverlapAll"));
    m_bCollisionActive = false;
    
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

    // Move bullet in direction
    m_vPosition += m_vVelocity*DeltaTime;
    SetActorLocation(m_vPosition);

    if (m_vPosition.Size() > KILL_RADIUS)
    {
        Destroy();
    }

    UpdateComponentTransforms();
}

void ABullet::Fire(FVector vPosition,
                   FVector vVelocity)
{
    m_vPosition = vPosition;
    m_vVelocity = vVelocity;

    SetActorLocation(m_vPosition);

    UpdateComponentTransforms();
    UpdateOverlaps();

    // Set the collision flag to true so that the pill
    // does not collide at world coordinates <0,0,0>
    m_bCollisionActive = true;
}

