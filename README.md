# OpenMotion Telemetry Unreal Engine Plugin

## What is it?
This Unreal Engine plugin simplifies implementing Motion Telemetry output from an Unreal Engine Game.  

[Demo](web/OpenMotionUnrealTest.gif)

_This should work with Unreal Engine 5.1+_
## How does it work?
By subclassing Chaos Vehicle Physics' `ChaosWheeledVehicleMovementComponent`, it's simple to add this to a Chaos Vehicle. It reads standard information from the Chaos Vehicle like Pitch, Roll, Yaw, Speed, Gear, RPM, etc., formats this information into a packet, and sends it over UDP to a listening Motion Simulator software such as SimTools, FlyPT Mover or SimRacingStudio.

A [FlyPT Mover](https://www.flyptmover.com) profile is included for testing. This is configured for the [YawVR Emulator](https://yaw.one/emulator/winbuild.zip) to allow for testing entirely in software.

## How do I use this with Chaos Vehicles?
1. Download this plugin and add it to the `/Plugins` folder in your Unreal Engine 5 project with a Chaos Vehicle setup.
2. Open the Chaos Vehicle Blueprint.
3. Find the VehicleMovementComponent on the Vehicle

    ![VehicleMovementComponent](web/1.png)

4. Change it's `Component Class` to `OpenMotionChaosWheeledVehicleMovementComponent`

    ![Component Class](web/3.png)

5. Set the IP Address and Port you wish to send data to

    ![IP and Port](web/4.png)

With this, basic data should start to send.  
To customise or add to the Data being sent, modify the `UOpenMotionChaosWheeledVehicleMovementComponent::TickComponent()` function

## What if I don't use Chaos Vehicles?
The ChaosOpenMotionTelemetry Module talks directly to the OpenMotionTelemetry Module, which implements the core functionality of sending output data to a listening Motion Simulator software.

### C++
You can use `UOpenMotionChaosWheeledVehicleMovementComponent` as an example, but basically, you will want to create an OpenMotionTelemetry object:

	UdpSender = CreateDefaultSubobject<UOpenMotionUdpSender>("UdpSender");

	UdpSender->RemoteAddress = DestinationAddress;
	UdpSender->RemotePort = DestinationPort;

	UdpSender->InitializeUdpSender(TEXT("OpenMotionTelemetry"));

Then when you want to send data, create an `FVehicleData` struct:

	FVehicleData VehicleData;

Fill it with your data:

    VehicleData.Pitch = GetPawnOwner()->GetTransform().Rotator().Pitch;
    VehicleData.Roll = GetPawnOwner()->GetTransform().Rotator().Roll;
    VehicleData.Yaw = GetPawnOwner()->GetTransform().Rotator().Yaw;

Then send the struct with:

	UdpSender->SendPacket(VehicleData);

### Blueprint
Set up nodes like this, maybe on a Tick function, and wire up the information from your game to the `VehicleData` struct.

![Blueprint](web/5.png)