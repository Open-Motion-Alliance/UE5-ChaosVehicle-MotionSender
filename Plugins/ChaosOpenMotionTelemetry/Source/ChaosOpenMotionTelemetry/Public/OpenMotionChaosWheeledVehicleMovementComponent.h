/*
MIT License

Copyright(c) 2023 Open Motion Telemetry
*/

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "OpenMotionUdpSender.h"
#include "OpenMotionChaosWheeledVehicleMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class CHAOSOPENMOTIONTELEMETRY_API UOpenMotionChaosWheeledVehicleMovementComponent : public UChaosWheeledVehicleMovementComponent
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, Category="Open Motion")
	FString DestinationAddress = "127.0.0.1";
	
	UPROPERTY(EditAnywhere, Category="Open Motion")
	int32 DestinationPort = 5999;
	
	UPROPERTY(EditAnywhere, Category="Open Motion")
	bool bIsEnabled = true;
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(BlueprintReadWrite)
	UOpenMotionUdpSender* UdpSender;

private:
	FVector LastVelocity;
	float LastYaw;
};
