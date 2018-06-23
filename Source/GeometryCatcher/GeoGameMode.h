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

};
