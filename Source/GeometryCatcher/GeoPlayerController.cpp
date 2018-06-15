// Fill out your copyright notice in the Description page of Project Settings.

#include "GeoPlayerController.h"
#include "Engine.h"

AGeoPlayerController::AGeoPlayerController(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
}


void AGeoPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Purple, TEXT("I'm the controller!"));
    }
}

