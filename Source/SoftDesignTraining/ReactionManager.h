// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */

enum ReactionType
{
	ReactionType_Invalid,
	ReactionType_Bang,
	ReactionType_Bing,
	ReactionType_Boom,
	ReactionType_Count,
};

class SOFTDESIGNTRAINING_API ReactionManager
{
private:
	ReactionManager();

	static ReactionManager* m_Instance;

public:
	TArray<ACharacter*> m_NPCList;

public:
	static ReactionManager* GetInstance();
	static void Destroy();

	void RegisterNPC(ACharacter* npcCharacter);
	void UnregisterNPC(ACharacter* npcCharacter);

	void CreateReactionEvent(FVector targetPosition, float radius, ReactionType reactionType);
};
