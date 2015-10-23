// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "SoftDesignTraining.h"
#include "SoftDesignTrainingPlayerController.h"
#include "AI/Navigation/NavigationSystem.h"
#include "SoftDesignTrainingCharacter.h"

#include "DesignTrainingMovementComponent.h"

#include "DrawDebugHelpers.h"

ASoftDesignTrainingPlayerController::ASoftDesignTrainingPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ASoftDesignTrainingPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}

void ASoftDesignTrainingPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ASoftDesignTrainingPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ASoftDesignTrainingPlayerController::OnSetDestinationReleased);
    InputComponent->BindAction("TakeCover", IE_Pressed, this, &ASoftDesignTrainingPlayerController::OnTakeCoverPressed);

	InputComponent->BindAction("PlaceBomb", IE_Pressed, this, &ASoftDesignTrainingPlayerController::OnPlaceBombPressed);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ASoftDesignTrainingPlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ASoftDesignTrainingPlayerController::MoveToTouchLocation);

    InputComponent->BindAxis("MoveForward", this, &ASoftDesignTrainingPlayerController::MoveForward);
    InputComponent->BindAxis("MoveRight", this, &ASoftDesignTrainingPlayerController::MoveRight);
}

void ASoftDesignTrainingPlayerController::MoveToMouseCursor()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(Hit.ImpactPoint);
	}
}

void ASoftDesignTrainingPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void ASoftDesignTrainingPlayerController::SetNewMoveDestination(const FVector& DestLocation)
{
	APawn* const Pawn = GetPawn();
	if (Pawn)
	{
		UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
		float const Distance = FVector::Dist(DestLocation, Pawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if (NavSys && (Distance > 120.0f))
		{
			NavSys->SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void ASoftDesignTrainingPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void ASoftDesignTrainingPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

void ASoftDesignTrainingPlayerController::MoveForward(float value)
{
    APawn* const Pawn = GetPawn();

    if (Pawn)
    {
        Pawn->AddMovementInput(FVector(value, 0.0f, 0.0f));
    }
}

void ASoftDesignTrainingPlayerController::MoveRight(float value)
{
    APawn* const Pawn = GetPawn();

    if (Pawn)
    {
        Pawn->AddMovementInput(FVector(0.0f, value, 0.0f));
    }
}

void ASoftDesignTrainingPlayerController::OnTakeCoverPressed()
{
    APawn* const Pawn = GetPawn();

    if (Pawn)
    {
        FVector actorLocation = Pawn->GetActorLocation();
        FRotator actorRotation = Pawn->GetActorRotation();
        FVector coverTestStart = actorLocation;
        FVector coverTestEnd = actorLocation + 400.0f * actorRotation.Vector();

        UWorld* currentWorld = GetWorld();

        static FName InitialCoverSweepTestName = TEXT("InitialCoverSweepTest");
        FHitResult hitResult;
        FQuat shapeRot = FQuat::Identity;
        FCollisionShape collShape = FCollisionShape::MakeSphere(Pawn->GetSimpleCollisionRadius());
        FCollisionQueryParams collQueryParams(InitialCoverSweepTestName, false, Pawn);
        currentWorld->DebugDrawTraceTag = InitialCoverSweepTestName;
        FCollisionObjectQueryParams collObjQueryParams(ECC_WorldStatic);
        
        UDesignTrainingMovementComponent* charMovement = Cast<UDesignTrainingMovementComponent>(Pawn->GetMovementComponent());

        if (currentWorld->SweepSingleByObjectType(hitResult, coverTestStart, coverTestEnd, shapeRot, collObjQueryParams, collShape, collQueryParams))
        {
            if (charMovement->ValidateCover(hitResult))
            {
                MoveToCoverDestination(hitResult.Location);
            }
        }
    }
}

void ASoftDesignTrainingPlayerController::MoveToCoverDestination(const FVector& DestLocation)
{
    APawn* const Pawn = GetPawn();
    if (Pawn)
    {
        UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();       
        NavSys->SimpleMoveToLocation(this, DestLocation);
    }
}
void ASoftDesignTrainingPlayerController::OnPlaceBombPressed()
{
	APawn* const pawn = GetPawn();
	if (pawn)
	{
		ASoftDesignTrainingCharacter* sdtChar = Cast<ASoftDesignTrainingCharacter>(pawn);
		if (sdtChar )
		{
			sdtChar->PlaceBomb();
		}
	}
}
