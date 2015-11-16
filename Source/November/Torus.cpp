// Fill out your copyright notice in the Description page of Project Settings.

#include "November.h"
#include "Torus.h"

#define ROT_SPEED 5.0f

// Sets default values
ATorus::ATorus()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    m_pMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

    static ConstructorHelpers::FObjectFinder<UStaticMesh> ofMesh(TEXT("StaticMesh'/Game/StaticMeshes/torus.torus'"));

    if (ofMesh.Succeeded())
    {
        m_pMesh->SetStaticMesh(ofMesh.Object);
        m_pMesh->SetCollisionProfileName(TEXT("NoCollision"));
    }

    RootComponent = m_pMesh;

    m_fRotation = 0.0f;
}

// Called when the game starts or when spawned
void ATorus::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATorus::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

    m_fRotation += DeltaTime * ROT_SPEED;

    SetActorRotation(FRotator(0.0f, m_fRotation, 0.0f));

}

