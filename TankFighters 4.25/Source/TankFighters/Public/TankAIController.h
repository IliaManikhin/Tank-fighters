// Copyright Manikhin Ilia 2021

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

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

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);

	

	// How close can AI tank get
	UPROPERTY(EditDefaultsOnly, Category = "Setup") 
	float AcceptanceRadius = 8000;

private:
	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void OnPosessedTankDeath();
};
