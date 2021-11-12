// Copyright Manikhin Ilia 2021

#include "TankAimingComponent.h"
#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Tank.h" // So we can use OnDeath

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	FoundAimingComponent(AimingComponent);
	
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );
	
	 AimTowardsCrosshair();

}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PosessedTank = Cast<ATank>(InPawn);
		if (!ensure(PosessedTank)) { return; }
		// Subscribe our local method to OnDeath
		PosessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPosessedTankDeath);
	}
}


void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; } // if we not possess pawn 
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector HitLocation; // OUT parameter 

	if(GetSightRayHitLocation(HitLocation))  // has a "side-effect", is going to line trace 
	{ 
	
		AimingComponent->AimAt(HitLocation);
	// TODO tell controlled tank to aim this point 
	}
}

// Get world location  of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	FVector LookDirection;
	// De-project the crosshair position to a world direction
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		//Line trace along that look direction, and see what we hit (up to max range)
		return GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	

	return false;
} 

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;

	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if( GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Camera)
		)
		{

		HitLocation = HitResult.Location;
		return true;

		}
	HitLocation = FVector(0);
		return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; // to be erased 

	return DeprojectScreenPositionToWorld
	(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	);

}

void ATankPlayerController::OnPosessedTankDeath()
{
	StartSpectatingOnly();
	UE_LOG(LogTemp, Warning, TEXT("PLAYER PLAYER IS DEAD , DELEGATE SAY"))
}
