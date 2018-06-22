// Fill out your copyright notice in the Description page of Project Settings.

#include "GeoEnemyPawn.h"
#include "GeoPlayerPawn.h"
#include "GeoGameMode.h"
#include "Engine.h"

// Sets default values
AGeoEnemyPawn::AGeoEnemyPawn(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Root component reacts to physics
        // Root component reacts to physics
    USphereComponent *CollisionComponent = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("RootComponent"));
    CollisionComponent->InitSphereRadius(50.0f);
    CollisionComponent->SetCollisionProfileName("Enemy");
    CollisionComponent->SetNotifyRigidBodyCollision(true);
    CollisionComponent->OnComponentHit.AddDynamic(this, &AGeoEnemyPawn::OnHit);
    RootComponent = CollisionComponent;

    // Create the visual component
    VisualComponent = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("VisualComponent"));
    VisualComponent->SetupAttachment(RootComponent);

    InitialLifeSpan = 2.0f;
}

// Called when the game starts or when spawned
void AGeoEnemyPawn::BeginPlay()
{
    Super::BeginPlay();

    
}

// Called every frame
void AGeoEnemyPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    
}

// Called to bind functionality to input
void AGeoEnemyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AGeoEnemyPawn::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
    AGeoPlayerPawn *PlayerPawn = dynamic_cast<AGeoPlayerPawn *>(OtherActor);
    if (OtherActor && OtherActor != this && OtherComp && PlayerPawn)
    {
        UWorld *World = GetWorld();

        OnEnemyHitPlayer.Broadcast(this);

        World->DestroyActor(this);
    }
}

void AGeoEnemyPawn::SetEnemyMesh(class UStaticMesh *Mesh)
{
    this->Mesh = Mesh;
    VisualComponent->SetStaticMesh(Mesh);
}

void AGeoEnemyPawn::SetEnemyMaterial(class UMaterialInstance *Material)
{
    this->MaterialInstance = Material;
    VisualComponent->SetMaterial(0, MaterialInstance);
}
