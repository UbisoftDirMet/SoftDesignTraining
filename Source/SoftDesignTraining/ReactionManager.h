// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ReactionEvent.h"

/**
 * 
 */

class SOFTDESIGNTRAINING_API ReactionManager
{
private:
	ReactionManager();

	static ReactionManager* m_Instance;

public:
	TArray<AActor*> m_NPCList;

public:
	static ReactionManager* GetInstance();
	static void Destroy();

	void RegisterNPC(AActor* npcCharacter);
	void UnregisterNPC(AActor* npcCharacter);

	void CreateReactionEvent(FVector targetPosition, float radius, ReactionType reactionType, ReactionLOS reactionLOS);
};
