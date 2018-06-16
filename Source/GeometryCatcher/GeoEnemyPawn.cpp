// Fill out your copyright notice in the Description page of Project Settings.

#include "GeoEnemyPawn.h"
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
    UStaticMeshComponent *VisualComponent = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("VisualComponent"));
    VisualComponent->SetupAttachment(RootComponent);
    static ConstructorHelpers::FObjectFinder<UStaticMesh> EnemyVisualAsset(TEXT("StaticMesh'/Game/Meshes/SM_Enemy_Cone.SM_Enemy_Cone'"));
    if (EnemyVisualAsset.Succeeded())
    {
        VisualComponent->SetStaticMesh(EnemyVisualAsset.Object);
    }

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
    if (OtherActor && OtherActor != this && OtherComp)
    {
        UWorld *World = GetWorld();
        World->DestroyActor(this);
    }
}
