// Fill out your copyright notice in the Description page of Project Settings.

#include "November.h"
#include "GameStats.h"

#define DEFAULT_HEALTH 10


int32 AGameStats::Wave   = 1;
int32 AGameStats::Health = DEFAULT_HEALTH;
int32 AGameStats::Score  = 0;
int32 AGameStats::Update = 0;


// Sets default values
AGameStats::AGameStats()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameStats::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameStats::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

int32 AGameStats::GetWave()
{
    return Wave;
}

int32 AGameStats::GetHealth()
{
    return Health;
}

int32 AGameStats::GetScore()
{
    return Score;
}

int32 AGameStats::GetUpdate()
{
    if (Update != 0)
    {
        Update = 0;
        return 1;
    }
    else
    {
        return 0;
    }
}

void AGameStats::ResetValues()
{
    Wave   = 1;
    Health = DEFAULT_HEALTH;
    Score  = 0;
}
