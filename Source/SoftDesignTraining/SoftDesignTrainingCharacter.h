// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "SoftDesignTrainingCharacter.generated.h"

UCLASS(Blueprintable)
class ASoftDesignTrainingCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;


public:
	ASoftDesignTrainingCharacter();

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }


    /** Set by character movement to specify that this Character is currently in cover. */
    //UPROPERTY(BlueprintReadOnly, replicatedUsing = OnRep_IsCrouched, Category = Character)
    UPROPERTY(BlueprintReadOnly, Category = Character)
    uint32 bIsInHighCover : 1;

    UPROPERTY(BlueprintReadOnly, Category = Character)
    uint32 bIsInLowCover : 1;

    UPROPERTY(BlueprintReadOnly, Category = Character)
    uint32 bIsInCover : 1;

    UFUNCTION(BlueprintCallable, Category = "Pawn|Character")
        virtual void Cover(const FVector& worldPosition);

    UFUNCTION(BlueprintCallable, Category = "Pawn|Character")
        virtual void StopCover();
};

