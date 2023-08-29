/*
MIT License

Copyright(c) 2023 Open Motion Telemetry
*/

#include "OpenMotionUdpSender.h"
#include "VehicleData.h"

UOpenMotionUdpSender::UOpenMotionUdpSender()
{
	SenderSocket = NULL;
}

UOpenMotionUdpSender::~UOpenMotionUdpSender()
{
	if(SenderSocket)
	{
		SenderSocket->Close();
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(SenderSocket);
	}
}

bool UOpenMotionUdpSender::InitializeUdpSender(const FString& SocketName)
{	
	//Create Remote Address.
	RemoteAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	
	bool bIsValid;
	RemoteAddr->SetIp(*RemoteAddress, bIsValid);
	RemoteAddr->SetPort(RemotePort);
	 
	if(!bIsValid)
	{
        const FString Str = "Open Motion UDP Sender - IP address not valid!";
		UE_LOG(LogTemp,Error,TEXT("%s"),*Str);
		return false;
	}
	 
	SenderSocket = FUdpSocketBuilder(*SocketName)
		.AsReusable()
		.WithBroadcast();
	
	//Set Send Buffer Size
	int32 SendSize = 2*1024*1024;
	SenderSocket->SetSendBufferSize(SendSize,SendSize);
	SenderSocket->SetReceiveBufferSize(SendSize, SendSize);
	
	UE_LOG(LogTemp,Log,TEXT("OpenMotion UDP Sender Started"));

	return true;
}

bool UOpenMotionUdpSender::SendPacket(FVehicleData Data)
{
	if(!bIsEnabled)
	{
		return false;
	}
	
	if(!SenderSocket) 
	{
    	UE_LOG(LogTemp,Log,TEXT("No sender socket"));
		return false;
	}
	
	int32 BytesSent = 0;
	
	FArrayWriter Writer;
	
	Writer << Data; //Serializing our custom data
	
	SenderSocket->SendTo(Writer.GetData(), Writer.Num(), BytesSent, *RemoteAddr);
	 
	if(BytesSent <= 0)
	{
		const FString Str = "Socket is valid but the receiver received 0 bytes, make sure it is listening properly!";
		UE_LOG(LogTemp,Error,TEXT("%s"),*Str);
		return false;
	}
	
	return true;
}
