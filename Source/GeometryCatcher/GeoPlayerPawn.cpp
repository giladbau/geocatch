// Fill out your copyright notice in the Description page of Project Settings.

#include "GeoPlayerPawn.h"
#include "Engine.h"
#include "GeoMovementComponent.h"
#include "ConstructorHelpers.h"

// Sets default values
AGeoPlayerPawn::AGeoPlayerPawn(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Root component reacts to physics
    UBoxComponent *CollisionComponent = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("RootComponent"));
    CollisionComponent->InitBoxExtent(FVector(50.0f, 50.0f, 50.0f));
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
    CameraComponent->SetAspectRatio(CameraWidth / CameraHeight);
    CameraComponent->SetOrthoWidth(CameraWidth);
    CameraComponent->SetWorldLocation(FVector(-500.0f, CameraWidth / 2.0f, CameraHeight / 2.0f));
}

// Called when the game starts or when spawned
void AGeoPlayerPawn::BeginPlay()
{
    Super::BeginPlay();
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
