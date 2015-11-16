// Fill out your copyright notice in the Description page of Project Settings.

#include "November.h"
#include "MenuPawn.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AMenuPawn::AMenuPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    m_nCurPos = 0;

}

// Called when the game starts or when spawned
void AMenuPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMenuPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );


}

// Called to bind functionality to input
void AMenuPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

    InputComponent->BindAction("MenuUp", EInputEvent::IE_Pressed,this, &AMenuPawn::Up);
    InputComponent->BindAction("MenuDown", EInputEvent::IE_Pressed, this, &AMenuPawn::Down);
    InputComponent->BindAction("MenuStart", EInputEvent::IE_Pressed, this, &AMenuPawn::Start);
    InputComponent->BindAction("MenuBack", EInputEvent::IE_Pressed, this, &AMenuPawn::Back);

}

void AMenuPawn::Up()
{
    if (m_nCurPos != 3)
    {
        m_nCurPos--;

        if (m_nCurPos < 0)
        {
            m_nCurPos = 0;
        }
    }
}

void AMenuPawn::Down()
{
    if (m_nCurPos != 3)
    {
        m_nCurPos++;

        if (m_nCurPos >= 3)
        {
            m_nCurPos = 2;
        }
    }
}

void AMenuPawn::Start()
{
    if (m_nCurPos == 0)
    {
        UGameplayStatics::OpenLevel(this, TEXT("GameLevel"));
    }
    else if (m_nCurPos == 1)
    {
        m_nCurPos = 3;
    }
    else if (m_nCurPos == 2)
    {
       UKismetSystemLibrary::QuitGame(this, UGameplayStatics::GetPlayerController(this,0), EQuitPreference::Quit);
    }
    else if (m_nCurPos == 3)
    {
        m_nCurPos = 0;
    }

}

void AMenuPawn::Back()
{
    m_nCurPos = 0;
}

int32 AMenuPawn::GetCurPos()
{
    return m_nCurPos;
}
