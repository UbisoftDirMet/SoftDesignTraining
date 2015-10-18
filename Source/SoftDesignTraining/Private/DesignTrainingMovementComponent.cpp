// Fill out your copyright notice in the Description page of Project Settings.

#include "SoftDesignTraining.h"
#include "DesignTrainingMovementComponent.h"

void UDesignTrainingMovementComponent::SetUpdatedComponent(USceneComponent* NewUpdatedComponent)
{
    Super::SetUpdatedComponent(NewUpdatedComponent);

    SoftDesignCharacterOwner = Cast<ASoftDesignTrainingCharacter>(GetPawnOwner());
}

void UDesignTrainingMovementComponent::InitializeComponent()
{
    Super::InitializeComponent();
}

void UDesignTrainingMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UDesignTrainingMovementComponent::TakeCover(const FVector& worldPosition)
{
    SoftDesignCharacterOwner->bIsInCover = true;
}

void UDesignTrainingMovementComponent::StopCover()
{
    SoftDesignCharacterOwner->bIsInCover = false;
}

bool UDesignTrainingMovementComponent::ValidateCover(FHitResult& coverHitResult)
{
    return true;
}
