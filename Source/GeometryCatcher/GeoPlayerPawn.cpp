// Fill out your copyright notice in the Description page of Project Settings.

#include "GeoPlayerPawn.h"
#include <Engine.h>
#include "GeoMovementComponent.h"
#include <ConstructorHelpers.h>

// Sets default values
AGeoPlayerPawn::AGeoPlayerPawn(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Root component reacts to physics
    UBoxComponent *CollisionComponent = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("RootComponent"));
    CollisionComponent->InitBoxExtent(FVector(100.0f, 100.0f, 100.0f));
    CollisionComponent->SetCollisionProfileName("Pawn");
    RootComponent = CollisionComponent;

    // Create the visual component
    UStaticMeshComponent *VisualComponent = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("VisualComponent"));
    VisualComponent->SetupAttachment(RootComponent);
    static ConstructorHelpers::FObjectFinder<UStaticMesh> BoxVisualAsset(TEXT("StaticMesh'/Game/Meshes/SM_Player.SM_Player'"));
    if (BoxVisualAsset.Succeeded())
    {
        VisualComponent->SetStaticMesh(BoxVisualAsset.Object);
    }

    // Connect to the movement component
    MovementComponent = ObjectInitializer.CreateDefaultSubobject<UGeoMovementComponent>(this, TEXT("MovementComponent"));
    MovementComponent->MaxSpeed = 5000.0f;
    MovementComponent->UpdatedComponent = CollisionComponent;

    // Static Camera
    CameraComponent = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("CameraComponent"));
    CameraComponent->SetProjectionMode(ECameraProjectionMode::Orthographic);
    CameraComponent->bConstrainAspectRatio = true;
    CameraComponent->SetAspectRatio(1920.0f / 1080.0f);
    CameraComponent->SetOrthoWidth(1920.0f);
    CameraComponent->SetWorldLocation(FVector(-500.0f, 960.0f, 540.0f));
}

// Called when the game starts or when spawned
void AGeoPlayerPawn::BeginPlay()
{
    Super::BeginPlay();
    
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Orange, TEXT("I'm the catcher!"));
    }    
}

// Called every frame
void AGeoPlayerPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGeoPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    
    PlayerInputComponent->BindAxis("MouseMoveH", this, &AGeoPlayerPawn::MouseMoveH);
}

UPawnMovementComponent* AGeoPlayerPawn::GetMovementComponent() const
{
    return MovementComponent;
}

void AGeoPlayerPawn::MouseMoveH(float Delta)
{
    if (MovementComponent != nullptr && Delta != 0.0f)
    {
        MovementComponent->AddInputVector(GetActorRightVector() * Delta);
    }
}
