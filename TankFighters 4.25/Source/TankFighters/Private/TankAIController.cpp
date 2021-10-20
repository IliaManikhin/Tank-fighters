// Fill out your copyright notice in the Description page of Project Settings.

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
		//TODO Move towards the player

		//Aim towards the player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		//Shoot if we ready
		ControlledTank->Fire(); // TODO dont fire every frame
	}

}


