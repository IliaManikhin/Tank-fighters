// Copyright Manikhin Ilia 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

//class UBoxComponent;

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
	UTankTrack();

	virtual void BeginPlay() override;

	void ApplySidewaysForce();

	// Max force per tack, in Newtons 
	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForce = 400000; // We get 40 tonne mass tank and acceleration 10 m/s

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void DriveTrack();

	float CurrentThrottle = 0;
};