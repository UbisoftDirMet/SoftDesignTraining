// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "ReactionEvent.h"

#include "AIBase.generated.h"

class UPatrolPathComponent;

UCLASS()
class SOFTDESIGNTRAINING_API AAIBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIBase();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);
	//virtual void EndPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	virtual void SetNewMoveDestination(const FVector DestLocation);
	virtual void ProcessReaction( ReactionEvent* reactionEvent);

private:
	unsigned long m_CurrentWayPoint;
	UPatrolPathComponent* m_PatrolPath;
	FVector m_NextDestination;

	bool m_IsBlind;
	float m_BlindTimeLeft;

};
