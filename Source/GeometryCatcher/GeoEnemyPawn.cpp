// Fill out your copyright notice in the Description page of Project Settings.

#include "GeoEnemyPawn.h"


// Sets default values
AGeoEnemyPawn::AGeoEnemyPawn(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void AGeoEnemyPawn::BeginPlay()
{
    Super::BeginPlay();
    
}

// Called every frame
void AGeoEnemyPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    
}

// Called to bind functionality to input
void AGeoEnemyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

}

