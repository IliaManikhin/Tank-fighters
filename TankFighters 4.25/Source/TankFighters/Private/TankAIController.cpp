// Copyright Manikhin Ilia 2021

#include "TankAimingComponent.h"
#include "TankAIController.h"
#include "Tank.h" // So we can impliment OnDeath, because this clas have no info about ATank


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PosessedTank = Cast<ATank>(InPawn);
		if (!ensure(PosessedTank)) { return; }
		// Subscribe our local method to OnDeath
		PosessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPosessedTankDeath);
	}

	 

}

void ATankAIController::Tick(float DeltaTime)
{
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(PlayerTank && ControlledTank && AimingComponent)) { return; }
	

		//Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius); //Check radius in cm

		//Aim towards the player
		AimingComponent->AimAt(PlayerTank->GetActorLocation());

		//Shoot if we ready
		if (AimingComponent->GetFiringState() == EFiringState::Locked)
		{
			AimingComponent->Fire();
		}

}

void ATankAIController::OnPosessedTankDeath()
{
	
	if (!ensure(GetPawn())) { return; } // TODO remove if ok 

	GetPawn()->DetachFromControllerPendingDestroy();

}


