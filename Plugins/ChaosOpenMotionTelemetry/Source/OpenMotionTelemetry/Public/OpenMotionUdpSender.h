/*
MIT License

Copyright(c) 2023 Open Motion Telemetry
*/

#pragma once

//Networking
#include "Networking.h"
#include "VehicleData.h"

//Base
#include "OpenMotionUdpSender.generated.h"

UCLASS()
class OPENMOTIONTELEMETRY_API UOpenMotionUdpSender : public UObject
{
	GENERATED_BODY()
	
public:

    UOpenMotionUdpSender();
	virtual ~UOpenMotionUdpSender() override;

	UPROPERTY(BlueprintReadWrite)
	FString RemoteAddress = "127.0.0.1";

	UPROPERTY(BlueprintReadWrite)
	int32 RemotePort = 5999;

	UPROPERTY(BlueprintReadWrite)
	bool bIsEnabled = true;
	
	bool InitializeUdpSender(
		const FString& SocketName
	);	
	
	UFUNCTION(BlueprintCallable, Category=OpenMotionUdpSender)
	bool SendPacket(FVehicleData Data);

protected:
	TSharedPtr<FInternetAddr> RemoteAddr;
	
	FSocket* SenderSocket;

};