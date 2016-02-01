// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "GameOverPawn.generated.h"

UCLASS()
class NOVEMBER_API AGameOverPawn : public APawn
{
	GENERATED_BODY()

public:

    //******
    // The whole point of GameOverPawn is to spawn a pawn
    // that has no visual component and does nothing because 
    // when at the game over screen, there doesn't need to be
    // a pawn spawned. I'm sure there is a better way to
    // to approach the problem, but for the gamejam, this was
    // fast to implement and it worked fine.
    //******


	// Sets default values for this pawn's properties
	AGameOverPawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	
	
};
