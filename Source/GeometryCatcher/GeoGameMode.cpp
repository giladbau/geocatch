// Fill out your copyright notice in the Description page of Project Settings.

#include "GeoGameMode.h"
#include "GeoEnemyPawn.h"
#include "GeoEnemySpawner.h"
#include "Engine.h"
#include "ConstructorHelpers.h"

AGeoGameMode::AGeoGameMode(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBP(TEXT("Pawn'/Game/Blueprints/BP_Player.BP_Player_C'"));
    if (PlayerPawnBP.Succeeded())
    {
        DefaultPawnClass = PlayerPawnBP.Class;
    }

    static ConstructorHelpers::FClassFinder<AController> PlayerControllerBP(TEXT("Controller'/Game/Blueprints/BP_PlayerController.BP_PlayerController_C'"));

    if (PlayerControllerBP.Succeeded())
    {
        PlayerControllerClass = PlayerControllerBP.Class;
    }

    static ConstructorHelpers::FClassFinder<AActor> EnemySpawnerBP(TEXT("AActor'/Game/Blueprints/BP_EnemySpawner.BP_EnemySpawner_C'"));

    if (EnemySpawnerBP.Succeeded())
    {
        EnemySpawnerClass = EnemySpawnerBP.Class;
    }
}

void AGeoGameMode::StartPlay()
{
    Super::StartPlay();

    UWorld *World = GetWorld();
    FVector EnemySpawnerLocation(0.0f, 960.0f, 1000.0f);
    EnemySpawner = World->SpawnActor<AGeoEnemySpawner>(EnemySpawnerClass, EnemySpawnerLocation, FRotator::ZeroRotator);
    EnemySpawner->OnEnemySpawned.AddUObject(this, &AGeoGameMode::OnEnemySpawned);
}

void AGeoGameMode::OnEnemySpawned(AGeoEnemyPawn *Enemy)
{
    Enemy->OnEnemyHitPlayer.AddUObject(this, &AGeoGameMode::OnEnemyHitPlayer);
}

void AGeoGameMode::OnEnemyHitPlayer(AGeoEnemyPawn *Enemy)
{
    HitCount++;
    //IncrementKillPoints();
}
