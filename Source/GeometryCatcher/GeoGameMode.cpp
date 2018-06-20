// Fill out your copyright notice in the Description page of Project Settings.

#include "GeoGameMode.h"
#include "Engine.h"
#include "ConstructorHelpers.h"

AGeoGameMode::AGeoGameMode(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBP(TEXT("Pawn'/Game/Blueprints/BP_Player.BP_Player_C'"));
    if (PlayerPawnBP.Succeeded())
    {
        DefaultPawnClass = PlayerPawnBP.Class;
    }

    static ConstructorHelpers::FClassFinder<AController> PlayerControllerBP(TEXT("Controller'/Game/Blueprints/BP_PlayerController.BP_PlayerController_C'"));

    if (PlayerControllerBP.Succeeded())
    {
        PlayerControllerClass = PlayerControllerBP.Class;
    }

    static ConstructorHelpers::FClassFinder<AHUD> PlayerHUDBP(TEXT("AHUD'/Game/Blueprints/BP_HUD.BP_HUD_C'"));

    if (PlayerHUDBP.Succeeded())
    {
        HUDClass = PlayerHUDBP.Class;
    }
}

void AGeoGameMode::StartPlay()
{
    Super::StartPlay();

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald, TEXT("Gentlemen, start your catching!"));
    }

    //WidgetBlueprint'/Game/UI/BP_HUD_Widget.BP_HUD_Widget'
}


