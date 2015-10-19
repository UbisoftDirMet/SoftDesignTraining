// Fill out your copyright notice in the Description page of Project Settings.

#include "SoftDesignTraining.h"
#include "AIBase.h"
#include "DrawDebugHelpers.h"
#include "ReactionManager.h"

// Sets default values
AAIBase::AAIBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAIBase::BeginPlay()
{
	Super::BeginPlay();

	ReactionManager* reactionManager = ReactionManager::GetInstance();
	if (reactionManager)
	{
		reactionManager->RegisterNPC(this);
	}
}


void AAIBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	ReactionManager* reactionManager = ReactionManager::GetInstance();
	if (reactionManager)
	{
		reactionManager->UnregisterNPC(this);
	}
}

// Called every frame
void AAIBase::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	FVector actorLocation = GetActorLocation();

	if (actorLocation.X > 0)
	{
		SetActorLocation(actorLocation);
	}

	//DrawDebugLine(GetWorld(), actorLocation, FVector::ZeroVector, FColor::Green, false);
}

// Called to bind functionality to input
void AAIBase::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
}

