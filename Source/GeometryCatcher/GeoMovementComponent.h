// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GeoMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class GEOMETRYCATCHER_API UGeoMovementComponent : public UPawnMovementComponent
{
    GENERATED_BODY()

    UGeoMovementComponent(const FObjectInitializer& ObjectInitializer);
    
    void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Movement)
    float MaxSpeed;
};
