// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/CharacterMovementComponent.h"
#include "DesignTrainingMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class SOFTDESIGNTRAINING_API UDesignTrainingMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

protected:

    //Init
    virtual void InitializeComponent() override;

    //Tick
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
};
