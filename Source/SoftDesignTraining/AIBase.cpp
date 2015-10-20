// Fill out your copyright notice in the Description page of Project Settings.

#include "SoftDesignTraining.h"
#include "AIBase.h"
#include "DrawDebugHelpers.h"
#include "ReactionManager.h"
#include "PatrolPathManager.h"
#include "PatrolPathComponent.h"

// Sets default values
AAIBase::AAIBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	PrimaryActorTick.bCanEverTick = true;
	m_CurrentWayPoint = 0;
	m_PatrolPath = nullptr;
	
	m_IsBlind = false;
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

	PatrolPathManager* ppm = PatrolPathManager::GetInstance();
	if (ppm)
	{
		m_PatrolPath = ppm->GetRandomPath();
		m_CurrentWayPoint = rand() % m_PatrolPath->GetNWayPoints();
	}

	FVector actorLocation = GetActorLocation();
	m_NextDestination = actorLocation;

}


void AAIBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	ReactionManager* reactionManager = ReactionManager::GetInstance();
	if (reactionManager)
	{
		reactionManager->UnregisterNPC(this);
	}

	m_PatrolPath = nullptr;
}

// Called every frame
void AAIBase::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	FVector actorLocation = GetActorLocation();
	DrawDebugLine(GetWorld(), actorLocation, FVector::ZeroVector, FColor::Green, false);

	if (m_IsBlind)
	{
		if (m_BlindTimeLeft > 0)
		{
			m_BlindTimeLeft -= DeltaTime;
			SetNewMoveDestination(actorLocation);
			return;
		}
		else
		{
			m_BlindTimeLeft = 0.0f;
			m_IsBlind = false;

			if (m_PatrolPath)
			{
				m_PatrolPath->GetNextWayPoint(m_CurrentWayPoint, m_NextDestination);
				SetNewMoveDestination(m_NextDestination);
			}
		}
	}
	// check if we are close enough to our next destination
	if ((actorLocation - m_NextDestination).Size2D() < 50.f)
	{
		// on est rendu!! ouais!
		if (m_PatrolPath)
		{
			m_PatrolPath->GetNextWayPoint(m_CurrentWayPoint, m_NextDestination);
			SetNewMoveDestination(m_NextDestination);
		}
	}	
}

// Called to bind functionality to input
void AAIBase::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
}

void AAIBase::SetNewMoveDestination(const FVector DestLocation)
{
	UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
	NavSys->SimpleMoveToLocation(GetController(), DestLocation);
}

void AAIBase::ProcessReaction(ReactionEvent* reactionEvent)
{
	if (!reactionEvent )
		return;
	FVector npcPosition = GetActorLocation();
	FVector npcHead = npcPosition + FVector::UpVector * 200.0f;
	UWorld* npcWorld = GetWorld();

	DrawDebugSphere(npcWorld, npcHead, reactionEvent->m_ReactionLOS == ReactionLOS_Visual ? 50.0f : 60.0f, 32, reactionEvent->m_ReactionLOS == ReactionLOS_Visual ? FColor::Green : FColor::Red, false, reactionEvent->m_ReactionLOS == ReactionLOS_Visual ? 3.0f : 0.5f);

	if (reactionEvent->m_ReactionLOS == ReactionLOS_Visual)
	{
		m_IsBlind = true;
		m_BlindTimeLeft = 3.0f;
	}
}