// Copyright Manikhin Ilia 2021

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class TANKFIGHTERS_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
		virtual void BeginPlay() override;

		// Called every frame
		virtual void Tick(float DeltaTime) override;

private:
	// How close can AI tank get
	float AcceptanceRadius = 3000;
};
