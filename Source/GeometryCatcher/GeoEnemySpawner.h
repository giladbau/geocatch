// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RandomStream.h"
#include "GeoEnemySpawner.generated.h"

USTRUCT()
struct FMaterialWrapper
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, Category = Rendering)
    class UMaterialInstance *Material;

    // For garbage collector
    void Destroy()
    {
        Material = nullptr;
    }

    FMaterialWrapper() : Material(nullptr) {}
};

USTRUCT()
struct FMeshWrapper
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, Category = Rendering)
    class UStaticMesh *StaticMesh;

    // For garbage collector
    void Destroy()
    {
        StaticMesh = nullptr;
    }

    FMeshWrapper() : StaticMesh(nullptr) {}
};

DECLARE_MULTICAST_DELEGATE_OneParam(FEnemySpawnedDelegate, class AGeoEnemyPawn *);

UCLASS()
class GEOMETRYCATCHER_API AGeoEnemySpawner : public AActor
{
    GENERATED_BODY()
    
public:	
    // Sets default values for this actor's properties
    AGeoEnemySpawner(const FObjectInitializer& ObjectInitializer);

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:	
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Horizontal extent of the spawner in the world
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Size)
    float SpawnerExtent = 900.0f;
    
    // Spawn interval in seconds initial value
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Gameplay)
    float InitialSpawnInterval = 1.0f;

    //// How much time before spawner begins spawning faster (0.0f for never)
    //UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Size)
    //float SpawnIntervalDecreaseInterval = 60.0f;

    //// By how long to decrese the spawn interval
    //UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Size)
    //float SpawnIntervalDecreaseValue = 0.1f;

    // Spawn interval in seconds
    UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = Gameplay)
    float SpawnInterval;

    UFUNCTION()
    void SpawnEnemy();

    // Materials for spawned enemies are randomly selected from this list
    UPROPERTY(EditDefaultsOnly, Category = Rendering)
    TArray<FMaterialWrapper> Materials;

    // Mesh for spawned enemies are randomly selected from this list
    UPROPERTY(EditDefaultsOnly, Category = Rendering)
    TArray<FMeshWrapper> Meshes;

    FEnemySpawnedDelegate OnEnemySpawned;

private:
    // Determine when to spawn the next enemy
    float TimeToSpawn = 0.0f;

    // Randomly choose where the next enemy spawns
    FRandomStream EnemyLocationRandomStream;

    // Randomly choose the mesh of the next enemy
    FRandomStream EnemyMeshRandomStream;

    // Randomly choose the material of the next enemy
    FRandomStream EnemyMaterialRandomStream;

    TSubclassOf<class AGeoEnemyPawn> EnemyClass;

};
