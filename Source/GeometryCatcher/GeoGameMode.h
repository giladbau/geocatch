// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GeoGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GEOMETRYCATCHER_API AGeoGameMode : public AGameModeBase
{
    GENERATED_BODY()
    
    AGeoGameMode(const FObjectInitializer& ObjectInitializer);
    void StartPlay() override;

public:

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay)
    int32 HitCount = 0;

    UFUNCTION()
    void OnEnemySpawned(class AGeoEnemyPawn *Enemy);

    UFUNCTION()
    void OnEnemyHitPlayer(class AGeoEnemyPawn *Enemy);

//    UFUNCTION(BlueprintImplementableEvent, Category = Gameplay)
//    void IncrementKillPoints();

protected:
    class AGeoEnemySpawner *EnemySpawner;

    TSubclassOf<class AGeoEnemySpawner> EnemySpawnerClass;
};
