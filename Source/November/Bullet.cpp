#include "November.h"
#include "Bullet.h"

#define KILL_RADIUS 2000.0f

// Sets default values
ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = true;
    
    // Create mesh component/box components
    m_pMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    m_pBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));

    m_pBox->SetCollisionProfileName(TEXT("OverlapAll"));

    // Initialize collision enable flag
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

    // Move bullet in direction of velocity
    m_vPosition += m_vVelocity * DeltaTime;
    SetActorLocation(m_vPosition);

    // If magnitude of origin exceeds kill radius,
    // then destroy bullet.
    if (m_vPosition.Size() > KILL_RADIUS)
    {
        Destroy();
    }
    
    // Safety precaution for avoiding collisions at 0,0,0
    // This is probably unnecessary now because of m_bCollisionActive
    // Consider removing
    UpdateComponentTransforms();
}

void ABullet::Fire(FVector vPosition,
                   FVector vVelocity)
{
    m_vPosition = vPosition;
    m_vVelocity = vVelocity;

    // Set bullet to new location
    SetActorLocation(m_vPosition);

    // Update components to reflect new position
    // Or else... weird things can happen with where the
    // bullet overlaps objects at position <0,0,0>
    UpdateComponentTransforms();
    UpdateOverlaps();

    // Set the collision flag to true so that the pill
    // will start checking for collisions
    m_bCollisionActive = true;
}

