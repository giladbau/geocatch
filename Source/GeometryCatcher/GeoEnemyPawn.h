// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GeoEnemyPawn.generated.h"

UCLASS()
class GEOMETRYCATCHER_API AGeoEnemyPawn : public APawn
{
    GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
    AGeoEnemyPawn(const FObjectInitializer& ObjectInitializer);

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:	
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void SetEnemyMaterial(class UMaterialInstance *Material);

    UFUNCTION()
    void OnHit(class UPrimitiveComponent* HitComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

    UPROPERTY()
    UStaticMeshComponent *VisualComponent;

private:
    class UMaterialInstance *MaterialInstance;
};
