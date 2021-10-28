// Copyright Manikhin Ilia 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Track is used to set maximum driving force, and to apply forces to tank.
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class TANKFIGHTERS_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// Set throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);

private:
	// Max force per tack, in Newtons 
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 400000; // We get 40 tonne mass tank and acceleration 10 m/s

};
