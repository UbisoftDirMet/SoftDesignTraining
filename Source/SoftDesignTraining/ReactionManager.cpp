// Fill out your copyright notice in the Description page of Project Settings.

#include "SoftDesignTraining.h"
#include "ReactionManager.h"
#include "DrawDebugHelpers.h"

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

void ReactionManager::RegisterNPC(ACharacter* npcCharacter)
{
	m_NPCList.Add(npcCharacter);
}

void ReactionManager::UnregisterNPC(ACharacter* npcCharacter)
{
	m_NPCList.Remove(npcCharacter);
}

void ReactionManager::CreateReactionEvent(FVector targetPosition, float radiusSQ, ReactionType reactionType)
{
	int npcCount = m_NPCList.Num();
	for (int i = 0; i < npcCount; ++i )
	{
		ACharacter* npcChar = m_NPCList[i];
		if (npcChar)
		{
			FVector npcPosition = npcChar->GetActorLocation();
			FVector diffToNpc = npcPosition - targetPosition;
			float distNpc = diffToNpc.SizeSquared();

			if ( distNpc < radiusSQ)
			{ 
				UWorld* npcWorld = npcChar->GetWorld();
				DrawDebugSphere(npcWorld, npcPosition + FVector::UpVector * 200.0f, 50.0f, 32, FColor::Red, false, 5.0f);
			}
		}
	}
}