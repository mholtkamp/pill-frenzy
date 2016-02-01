// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "MenuPawn.generated.h"

UCLASS()
class NOVEMBER_API AMenuPawn : public APawn
{
	GENERATED_BODY()

public:

    //*****
    // This pawn is similar to the gameover pawn, but it also 
    // controls the state of the menu.
    //*****

	// Sets default values for this pawn's properties
	AMenuPawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

    void Down();

    void Up();

    void Start();

    void Back();

    int32 m_nCurPos;

    int32 m_nStart;

    int32 m_nBack;

    UFUNCTION(BlueprintCallable, Category = "Pill Frenzy Menu")
    int32 GetCurPos();

	
	
};
