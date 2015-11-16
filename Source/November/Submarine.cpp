// Fill out your copyright notice in the Description page of Project Settings.

#include "November.h"
#include "Submarine.h"
#include "Pill.h"
#include "GameStats.h"

#define STICK_DEAD_ZONE 0.1f
#define DEFAULT_SPEED 2.0f
#define DEFAULT_PROP_ROT_SPEED 180.0f

#define DEFAULT_HEALTH 10

#define BOUNDARY_LEFT -275.0f
#define BOUNDARY_RIGHT -100.0f
#define BOUNDARY_TOP 150.0f
#define BOUNDARY_BOTTOM -150.0f

#define PILL_SPEED 350.0f
#define PILL_OFFSET_X 40.0f

// Sets default values
ASubmarine::ASubmarine()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Object finders for meshes
    static ConstructorHelpers::FObjectFinder<UStaticMesh> ofSubMesh(TEXT("StaticMesh'/Game/StaticMeshes/sub.sub'"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> ofAxleMesh(TEXT("StaticMesh'/Game/StaticMeshes/axle.axle'"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> ofPropellerMesh(TEXT("StaticMesh'/Game/StaticMeshes/propeller.propeller'"));
    static ConstructorHelpers::FObjectFinder<UParticleSystem> ofBubbles(TEXT("ParticleSystem'/Game/ParticleSystems/P_SubBubbles.P_SubBubbles'"));

    // Create components
    m_pBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
    m_pSubMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sub Mesh"));
    m_pAxleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Axle Mesh"));
    m_pPropellerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Propeller Mesh"));
    m_pSideSpotlight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Side Spotlight"));
    m_pDirectSpotlight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Direct Spotlight"));
    m_pPointlight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Pointlight"));
    m_pBubbles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Bubbles"));

    // Setup components
    m_pBox->InitBoxExtent(FVector(105.0f, 220.0f, 105.0f));
    m_pBox->SetCollisionProfileName(TEXT("Pawn"));
    
    if (ofSubMesh.Succeeded()  &&
        ofAxleMesh.Succeeded() &&
        ofPropellerMesh.Succeeded() &&
        ofBubbles.Succeeded())
    {
        m_pSubMesh->SetStaticMesh(ofSubMesh.Object);
        m_pAxleMesh->SetStaticMesh(ofAxleMesh.Object);
        m_pPropellerMesh->SetStaticMesh(ofPropellerMesh.Object);
        m_pBubbles->SetTemplate(ofBubbles.Object);
    }

    m_pSideSpotlight->SetRelativeRotation(FRotator(0.0f, 215.0f, 0.0f));
    m_pSideSpotlight->SetRelativeLocation(FVector(0.0f, 0.0f, 250.0f));
    m_pSideSpotlight->SetIntensity(53000.0f);
    m_pSideSpotlight->SetLightColor(FColor::Yellow);
    m_pSideSpotlight->SetInnerConeAngle(2.0f);
    //m_pSideSpotlight->bUseInverseSquaredFalloff = 0;

    m_pDirectSpotlight->SetRelativeRotation(FRotator(0.0f, 290.0f, 0.0f));
    m_pDirectSpotlight->bUseInverseSquaredFalloff = 0;
    m_pDirectSpotlight->SetIntensity(420.0f);
    m_pDirectSpotlight->SetLightColor(FColor(0xFFAF00));


    m_pPointlight->SetIntensity(1850.0f);
    m_pPointlight->SetLightColor(FColor(0xFFA200));
    m_pPointlight->SetWorldLocation(FVector::ZeroVector);
    m_pPointlight->SetRelativeLocation(FVector(0.0f, -135.0f, 213.0f));

    m_pBubbles->SetRelativeLocation(FVector(0.0f, 278.0f, 0.0f));
    m_pBubbles->SetWorldScale3D(FVector(2.8f, 2.8f, 2.8f));

    // Set Root Component
    RootComponent = m_pBox;

    // Attach child components
    m_pSubMesh->AttachTo(RootComponent);
    m_pAxleMesh->AttachTo(RootComponent);
    m_pPropellerMesh->AttachTo(RootComponent);
    m_pSideSpotlight->AttachTo(RootComponent);
    m_pDirectSpotlight->AttachTo(RootComponent);
    m_pPointlight->AttachTo(RootComponent);
    m_pBubbles->AttachTo(RootComponent);

    // Rotate actor 90 degrees so it is facing the positive x direction
    SetActorRotation(FRotator(0.0f, 90.0f, 0.0f));
    SetActorScale3D(FVector(0.08f, 0.08f, 0.08f));

    // Initialize move direction to zero even though it is probably already
    // set to the zero vector in the constructor.
    m_vMoveDir.Set(0.0f, 0.0f, 0.0f);

    m_fSpeed = DEFAULT_SPEED;
    m_fPropRotSpeed = DEFAULT_PROP_ROT_SPEED;
    m_fPropRot = 0.0f;
    m_nHealth = DEFAULT_HEALTH;
}

// Called when the game starts or when spawned
void ASubmarine::BeginPlay()
{
	Super::BeginPlay();

    AActor* pCamera = 0;

    // Find the main camera
    for (TActorIterator<ACameraActor> it(GetWorld()); it; ++it)
    {
        if (it->GetName().Equals(TEXT("MainCamera")))
        {
            pCamera = *it;
        }
    }
    // Change the view target of player controller to the main static camera
    UGameplayStatics::GetPlayerController(this, 0)->SetViewTarget(pCamera);
	
}

// Called every frame
void ASubmarine::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

    // Update movement
    if (!m_vMoveDir.IsNearlyZero())
    {
        // The movement vector is nonzero, so the player wants to move the sub.
        m_vMoveDir.Normalize();

        FVector vNewLoc = GetActorLocation();
        vNewLoc += m_vMoveDir * m_fSpeed;
        

        // Ensure that new location is within movement zone.
        if (vNewLoc.X < BOUNDARY_LEFT)
        {
            vNewLoc.X = BOUNDARY_LEFT;
        }
        if (vNewLoc.X > BOUNDARY_RIGHT)
        {
            vNewLoc.X = BOUNDARY_RIGHT;
        }
        if (vNewLoc.Z > BOUNDARY_TOP)
        {
            vNewLoc.Z = BOUNDARY_TOP;
        }
        if (vNewLoc.Z < BOUNDARY_BOTTOM)
        {
            vNewLoc.Z = BOUNDARY_BOTTOM;
        }

        SetActorLocation(vNewLoc);
    }

    // Rotate the propellers!
    m_fPropRot += DeltaTime * m_fPropRotSpeed;

    m_pPropellerMesh->SetRelativeRotation(FRotator(-1 * m_fPropRot, 0.0f, 0.0f));

}

// Called to bind functionality to input
void ASubmarine::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

    InputComponent->BindAxis("MoveX", this, &ASubmarine::MoveX);
    InputComponent->BindAxis("MoveZ", this, &ASubmarine::MoveZ);
    InputComponent->BindAction("Fire",EInputEvent::IE_Pressed, this, &ASubmarine::Fire);

}

void ASubmarine::MoveX(float fAxisValue)
{
    m_vMoveDir.X = (FMath::Abs(fAxisValue) > STICK_DEAD_ZONE) ? fAxisValue : 0.0f;
}

void ASubmarine::MoveZ(float fAxisValue)
{
    m_vMoveDir.Z = (FMath::Abs(fAxisValue) > STICK_DEAD_ZONE) ? fAxisValue : 0.0f;
}

void ASubmarine::Fire()
{
    APill* pPill = GetWorld()->SpawnActor<APill>();

    if (pPill != 0)
    {
        pPill->Fire(GetActorLocation() + FVector(PILL_OFFSET_X, 0.0f, 0.0f),
                    FVector(PILL_SPEED, 0.0f, 0.0f));
    }
}

void ASubmarine::Damage(int32 nDamage)
{
    m_nHealth -= nDamage;
    AGameStats::Health = m_nHealth;
    AGameStats::Update = 1;

    if (m_nHealth <= 0)
    {
        UGameplayStatics::OpenLevel(this, TEXT("GameOverLevel"));
        //GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Green, TEXT("Game Over!"));
    }
}