// Fill out your copyright notice in the Description page of Project Settings.

#include "SoftDesignTraining.h"
#include "ReactionManager.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

ReactionManager* ReactionManager::m_Instance;

ReactionManager::ReactionManager()
{
}

ReactionManager* ReactionManager::GetInstance()
{
	if (!m_Instance)
	{
		m_Instance = new ReactionManager();
	}

	return m_Instance;
}

void ReactionManager::Destroy()
{
	delete m_Instance;
	m_Instance = nullptr;
}

void ReactionManager::RegisterNPC(AActor* npcCharacter)
{
	m_NPCList.Add(npcCharacter);
}

void ReactionManager::UnregisterNPC(AActor* npcCharacter)
{
	m_NPCList.Remove(npcCharacter);
}

void ReactionManager::CreateReactionEvent(FVector targetPosition, float radiusSQ, ReactionType reactionType, ReactionLOS reactionLOS)
{
	int npcCount = m_NPCList.Num();
	for (int i = 0; i < npcCount; ++i )
	{
		AActor* npcChar = m_NPCList[i];
		if (npcChar)
		{
			FVector npcPosition = npcChar->GetActorLocation();
			FVector diffToNpc = npcPosition - targetPosition;
			float distNpc = diffToNpc.SizeSquared();

			if ( distNpc < radiusSQ)
			{ 
				UWorld* npcWorld = npcChar->GetWorld();
				FVector npcHead = npcPosition + FVector::UpVector * 200.0f;
				bool hasHit = true;

				if (reactionLOS == ReactionLOS_Visual)
				{
					FVector targetHigh = targetPosition + FVector::UpVector * 100.0f;
					FHitResult hitData;
					FCollisionQueryParams TraceParams(FName(TEXT("VictoreCore Trace")), true);
					hasHit = !npcWorld->LineTraceSingleByChannel(hitData, npcHead, targetHigh, ECC_Pawn, TraceParams);
				}

				if ( hasHit )
				{
					DrawDebugSphere(npcWorld, npcHead, reactionLOS == ReactionLOS_Visual ? 50.0f : 60.0f, 32, reactionLOS == ReactionLOS_Visual ? FColor::Green : FColor::Red, false, 5.0f);
				}				
			}
		}
	}
}