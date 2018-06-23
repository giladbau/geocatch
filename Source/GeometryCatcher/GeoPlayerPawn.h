// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GeoPlayerPawn.generated.h"

UCLASS()
class GEOMETRYCATCHER_API AGeoPlayerPawn : public APawn
{
    GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
    AGeoPlayerPawn(const FObjectInitializer& ObjectInitializer);

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:	
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    virtual UPawnMovementComponent* GetMovementComponent() const override;

    UFUNCTION()
    void MouseMoveH(float Delta);

    // Camera viewport width
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Camera)
    float CameraWidth = 1920.0f;

    // Camera viewport height
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = Camera)
    float CameraHeight = 1080.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay)
    int32 HitCount = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
    TSubclassOf<class AGeoEnemySpawner> EnemySpawnerClass;

    UFUNCTION()
    void OnEnemySpawned(class AGeoEnemyPawn *Enemy);

    UFUNCTION()
    void OnEnemyHitPlayer(class AGeoEnemyPawn *Enemy);

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Gameplay)
    void IncrementKillPoints();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = true), Category = Movement)
    class UGeoMovementComponent *MovementComponent;

    class UCameraComponent *CameraComponent;

    class AGeoEnemySpawner *EnemySpawner;
};
