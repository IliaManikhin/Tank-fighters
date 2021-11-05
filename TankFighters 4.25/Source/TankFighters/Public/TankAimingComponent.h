// Copyright Manikhin Ilia 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for aiming state
UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

class UTankBarrel; // Forward declaration 
class UTankTurret;

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANKFIGHTERS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

public:	
	
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Setup")
	EFiringState FiringState = EFiringState::Reloading;

private:
	UTankBarrel* Barrel = nullptr;

	UTankTurret* Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000;

	void MoveBarrelTowards(FVector AimDirection);

};
