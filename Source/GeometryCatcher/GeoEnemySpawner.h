// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GeoEnemySpawner.generated.h"

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

    // Width of the spawner in the world
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Size)
    float WorldWidth = 1920;
    
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
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
    float SpawnInterval;

    UFUNCTION()
    void SpawnEnemy();

private:
    // Determine when to spawn the next enemy
    float TimeToSpawn = 0.0f;
};
