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

    EnemyLocationRandomStream.GenerateNewSeed();
    EnemyMeshRandomStream.GenerateNewSeed();
    EnemyMaterialRandomStream.GenerateNewSeed();

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
    
    SpawnInterval = InitialSpawnInterval;
}

void AGeoEnemySpawner::SpawnEnemy()
{
    UWorld *World = GetWorld();
    
    // Choose a random location to spawn within the horizontal extent
    const float SpawnLocationY = EnemyLocationRandomStream.FRandRange(GetActorLocation().Y - SpawnerExtent, GetActorLocation().Y + SpawnerExtent);
    const FVector SpawnLocation(0.0f, SpawnLocationY, GetActorLocation().Z);
    
    AGeoEnemyPawn* const Enemy = World->SpawnActor<AGeoEnemyPawn>(EnemyClass, SpawnLocation, FRotator::ZeroRotator);
    
    if (Meshes.Num() > 0)
    {
        int32 RandomMeshIndex = EnemyMeshRandomStream.RandRange(0, Meshes.Num() - 1);
        Enemy->SetEnemyMesh(Meshes[RandomMeshIndex].StaticMesh);
    }
    
    if (Materials.Num() > 0)
    {
        int32 RandomMaterialIndex = EnemyMaterialRandomStream.RandRange(0, Materials.Num() - 1);
        Enemy->SetEnemyMaterial(Materials[RandomMaterialIndex].Material);
    }
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

