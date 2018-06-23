// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GeoPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GEOMETRYCATCHER_API AGeoPlayerController : public APlayerController
{
    GENERATED_BODY()

    AGeoPlayerController(const FObjectInitializer& ObjectInitializer);
    
    void BeginPlay() override;

public:

};
