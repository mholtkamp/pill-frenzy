// Fill out your copyright notice in the Description page of Project Settings.

#include "November.h"
#include "GameOverPawn.h"


// Sets default values
AGameOverPawn::AGameOverPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameOverPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameOverPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AGameOverPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

