// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GameStats.generated.h"

UCLASS()
class NOVEMBER_API AGameStats : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameStats();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

    static int32 Wave;
    
    static int32 Health;

    static int32 Score;
    
    static int32 Update;
    
    UFUNCTION(BlueprintCallable, Category="Pill Frenzy Game Stats")
    static int32 GetWave();

    UFUNCTION(BlueprintCallable, Category="Pill Frenzy Game Stats")
    static int32 GetHealth();

    UFUNCTION(BlueprintCallable, Category="Pill Frenzy Game Stats")
    static int32 GetScore();

    UFUNCTION(BlueprintCallable, Category="Pill Frenzy Game Stats")
    static int32 GetUpdate();

	UFUNCTION(BlueprintCallable, Category="Pill Frenzy Game Stats")
    static void ResetValues();
	
};
