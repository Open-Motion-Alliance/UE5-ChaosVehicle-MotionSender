/*
MIT License

Copyright(c) 2023 Open Motion Telemetry
*/

#include "..\Public\OpenMotionChaosWheeledVehicleMovementComponent.h"

UOpenMotionChaosWheeledVehicleMovementComponent::UOpenMotionChaosWheeledVehicleMovementComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;

	UdpSender = CreateDefaultSubobject<UOpenMotionUdpSender>("UdpSender");

	UdpSender->RemoteAddress = DestinationAddress;
	UdpSender->RemotePort = DestinationPort;

	UdpSender->InitializeUdpSender(TEXT("OpenMotionTelemetry"));
}

void UOpenMotionChaosWheeledVehicleMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (UdpSender)
	{
		if(bIsEnabled && VehicleSimulationPT.Get())
		{
			const auto& PVehicle = VehicleSimulationPT.Get()->PVehicle.Get();

			FVehicleData VehicleData;
			
			// Calculate Local Velocity
			FVector VehicleVelocity = GetPawnOwner()->GetVelocity();
			FVector LocalVelocity = VehicleVelocity.Rotation().UnrotateVector(GetPawnOwner()->GetActorForwardVector());
			
			// Calculate Acceleration from Velocity
			FVector Acceleration = LocalVelocity - LastVelocity;
			Acceleration = Acceleration / 100;	// Meters
			Acceleration = Acceleration / DeltaTime;	// Seconds?
			
			auto& PEngine = PVehicle->GetEngine();
			auto& PTransmission = PVehicle->GetTransmission();

			VehicleData.Pitch = GetPawnOwner()->GetTransform().Rotator().Pitch;
			VehicleData.Roll = GetPawnOwner()->GetTransform().Rotator().Roll;
			float Yaw = GetPawnOwner()->GetActorForwardVector().Rotation().Yaw - VehicleVelocity.Rotation().Yaw;
			VehicleData.Yaw = PTransmission.GetCurrentGear() >= 0 ? Yaw : 0;
            
			VehicleData.Gear = PTransmission.GetCurrentGear();
			VehicleData.CurrentEngineRpm = PEngine.GetEngineRPM();
			VehicleData.EngineIdleRpm = PEngine.Setup().EngineIdleRPM;
			
			VehicleData.VelocityX = VehicleVelocity.X;
			VehicleData.VelocityY = VehicleVelocity.Y;
			VehicleData.VelocityZ = VehicleVelocity.Z;
			
			VehicleData.AccelerationX = Acceleration.X;
			VehicleData.AccelerationY = Acceleration.Y;
			VehicleData.AccelerationZ = Acceleration.Z;
			
			LastVelocity = LocalVelocity;
			
			UdpSender->SendPacket(VehicleData);
		}
	}
}
