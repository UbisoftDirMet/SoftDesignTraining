// Fill out your copyright notice in the Description page of Project Settings.

#include "SoftDesignTraining.h"
#include "PatrolPathComponent.h"


// Sets default values for this component's properties
UPatrolPathComponent::UPatrolPathComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UPatrolPathComponent::BeginPlay()
{
	Super::BeginPlay();
	//AActor* MyActor = m_Owner;
	//TArray<AActor*> MyActor_Children = MyActor->Children;

	// ...
	
}


// Called every frame
void UPatrolPathComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

