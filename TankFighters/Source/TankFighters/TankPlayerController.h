// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TANKFIGHTERS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// Tank start to move barrel so that a shoot would hit where
	// the crosshair intersects the world 
	void AimTowardsCrosshair();

private:
	ATank* GetControlledTank() const;
};
