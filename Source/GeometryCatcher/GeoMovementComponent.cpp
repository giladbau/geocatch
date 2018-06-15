// Fill out your copyright notice in the Description page of Project Settings.

#include "GeoMovementComponent.h"
#include "Engine.h"

UGeoMovementComponent::UGeoMovementComponent(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{

}

void UGeoMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // Make sure the component should update
    if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
    {
        return;
    }
    
    FVector DesiredMovementDir = ConsumeInputVector().GetClampedToSize(-1.0f, 1.0f) * DeltaTime * MaxSpeed;
    if (!DesiredMovementDir.IsNearlyZero())
    {
        FHitResult Hit;
        SafeMoveUpdatedComponent(DesiredMovementDir, UpdatedComponent->GetComponentRotation(), true, Hit);

        // Maybe handle collision if applicable.
    }
}
