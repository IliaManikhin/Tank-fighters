// Copyright Manikhin Ilia 2021

#include "Tank.h"
#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime)
{
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

	if (PlayerTank)
	{
		//Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius); //Check radius in cm

	
		//Aim towards the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		//Shoot if we ready
		ControlledTank->Fire(); // TODO dont fire every frame
	}

}


