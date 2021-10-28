// Copyright Manikhin Ilia 2021


#include "TankTrack.h"


void UTankTrack::SetThrottle(float Throttle)
{
	auto ForceAplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceAplied, ForceLocation); 

}

