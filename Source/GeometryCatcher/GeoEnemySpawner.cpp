// Fill out your copyright notice in the Description page of Project Settings.

#include "GeoEnemySpawner.h"
#include "Engine.h"
#include "GeoEnemyPawn.h"
#include "ConstructorHelpers.h"

// Sets default values
AGeoEnemySpawner::AGeoEnemySpawner(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    SpawnInterval = InitialSpawnInterval;
    
    // TODO: Later use GenerateRandomSeed
    EnemyLocationRandomStream.Initialize(999);

    static ConstructorHelpers::FObjectFinder<UBlueprint> EnemyBlueprint(TEXT("Blueprint'/Game/Blueprints/BP_Enemy.BP_Enemy'"));
    if (EnemyBlueprint.Succeeded())
    {
        EnemyClass = (UClass*)EnemyBlueprint.Object->GeneratedClass;
    }
}

// Called when the game starts or when spawned
void AGeoEnemySpawner::BeginPlay()
{
    Super::BeginPlay();
    
}

void AGeoEnemySpawner::SpawnEnemy()
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, TEXT("Spawned!"));
    }

    UWorld *World = GetWorld();
    
    // Choose a random location to spawn in
    const float SpawnLocationY = EnemyLocationRandomStream.FRandRange(0, SpawnerExtent);
    const FVector SpawnLocation(0.0f, SpawnLocationY, GetActorLocation().Z);
    
    AGeoEnemyPawn* const Enemy = World->SpawnActor<AGeoEnemyPawn>(EnemyClass, SpawnLocation, FRotator::ZeroRotator);
}

// Called every frame
void AGeoEnemySpawner::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    TimeToSpawn += DeltaTime;
    if (TimeToSpawn >= SpawnInterval)
    {
        // Spawn an enemy
        SpawnEnemy();

        // Adjust the timer
        TimeToSpawn -= SpawnInterval;
    }
}

