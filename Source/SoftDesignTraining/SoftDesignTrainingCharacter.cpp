// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "SoftDesignTraining.h"
#include "SoftDesignTrainingCharacter.h"
//#include "Engine/Public/DrawDebugHelpers.h"
#include "ReactionManager.h"
#include "DrawDebugHelpers.h"


ASoftDesignTrainingCharacter::ASoftDesignTrainingCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 2000.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

void ASoftDesignTrainingCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector currentLocation = GetActorLocation();

	ReactionManager* reactionManager = ReactionManager::GetInstance();
	if (reactionManager)
	{
		UWorld* currentWorld = GetWorld();

		int npcCount = reactionManager->m_NPCList.Num();

		for (int i = 0; i < npcCount; ++i)
		{
			AActor* npcCharacter = reactionManager->m_NPCList[i];
			if (npcCharacter)
			{
				DrawDebugLine(currentWorld, currentLocation, npcCharacter->GetActorLocation(), FColor::Red, false);
			}
		}
	}
}

void ASoftDesignTrainingCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ASoftDesignTrainingCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	ReactionManager* reactionManager = ReactionManager::GetInstance();
	if (reactionManager)
	{
		reactionManager->Destroy();
	}
}

void ASoftDesignTrainingCharacter::PlaceBomb()
{
	ReactionManager* reactionManager = ReactionManager::GetInstance();
	if (reactionManager)
	{
		reactionManager->CreateReactionEvent(GetActorLocation(), 6250000.0f, ReactionType_Boom, ReactionLOS_Sound);
		reactionManager->CreateReactionEvent(GetActorLocation(), 6250000.0f, ReactionType_Boom, ReactionLOS_Visual);
	}
}
