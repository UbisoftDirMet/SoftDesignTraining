// Fill out your copyright notice in the Description page of Project Settings.

#include "SoftDesignTraining.h"
#include "ReactionManager.h"

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
