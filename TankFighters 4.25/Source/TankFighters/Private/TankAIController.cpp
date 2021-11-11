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

	if (!ensure(PlayerTank && ControlledTank)) { return; }
	
	//Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius); //Check radius in cm

	
	//Aim towards the player
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	//Shoot if we ready
	if (AimingComponent->GetFiringState() == EFiringState::Locked)
	{
		AimingComponent->Fire(); // TODO dont fire every frame
	}
	


}

void ATankAIController::OnPosessedTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("TANK IS DEAD , DELEGATE SAY"))
}


