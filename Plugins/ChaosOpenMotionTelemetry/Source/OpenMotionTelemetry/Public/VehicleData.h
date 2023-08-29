#pragma once

/*
MIT License

Copyright(c) 2023 Open Motion Telemetry
*/

#pragma once
#include "VehicleData.generated.h"

USTRUCT(BlueprintType)
struct OPENMOTIONTELEMETRY_API FVehicleData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Open Motion")
	float Pitch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Open Motion")
	float Roll;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Open Motion")
	float Yaw;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Open Motion")
	int32 Gear;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Open Motion")
	float Speed; // meters per second

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Open Motion")
	float CurrentEngineRpm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Open Motion")
	float EngineMaxRpm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Open Motion")
	float EngineIdleRpm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Open Motion")
	float Power; // watts

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Open Motion")
	float Torque; // newton meter

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Open Motion")
	float AccelerationX; //In the car's local space; X = right, Y = up, Z = forward

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Open Motion")
	float AccelerationY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Open Motion")
	float AccelerationZ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Open Motion")
	float VelocityX; //In the car's local space; X = right, Y = up, Z = forward

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Open Motion")
	float VelocityY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Open Motion")
	float VelocityZ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Open Motion")
	float AngularVelocityX; //In the car's local space; X = pitch, Y = yaw, Z = roll

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Open Motion")
	float AngularVelocityY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Open Motion")
	float AngularVelocityZ;

	FVehicleData()
	{}
};

FORCEINLINE FArchive& operator<<(FArchive& Ar, FVehicleData& InData)
{
	Ar << InData.Pitch;
	Ar << InData.Roll;
	Ar << InData.Yaw;
	Ar << InData.VelocityX; //In the car's local space; X = right, Y = up, Z = forward
	Ar << InData.VelocityY;
	Ar << InData.VelocityZ;
	Ar << InData.AccelerationX; //In the car's local space; X = right, Y = up, Z = forward
	Ar << InData.AccelerationY;
	Ar << InData.AccelerationZ;
	Ar << InData.AngularVelocityX; //In the car's local space; X = pitch, Y = yaw, Z = roll
	Ar << InData.AngularVelocityY;
	Ar << InData.AngularVelocityZ;
	// Other Data
	Ar << InData.Gear;
	Ar << InData.Speed;
	Ar << InData.CurrentEngineRpm;
	Ar << InData.EngineMaxRpm;
	Ar << InData.EngineIdleRpm;

}