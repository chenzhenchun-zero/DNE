#pragma once

#include "CoreMinimal.h"
#include "Misc/Paths.h"
#include "Engine/World.h"
#include "DNEVPrivatePCH.h"
#include "DNEVMeshComponent.h"

#include <string>

inline FMatrix DNEVToUnrealCoordinates()
{
	return FMatrix(
		FVector(0, 1, 0),
		FVector(0, 0, 1),
		FVector(-1, 0, 0),
		FVector(0, 0, 0)
	);
}

inline FVector DNEVToUnrealVector(const FVector& vector)
{
	return DNEVToUnrealCoordinates().TransformVector(vector);
}

inline FVector DNEVToUnrealPosition(const FVector& pos)
{
	return DNEVToUnrealCoordinates().TransformPosition(pos);
}

inline FVector DNEVToUnrealScale(const FVector& vector)
{
	return vector * 0.1f;
}

inline FString GetContentDNEVDataPath(FString DataName)
{
	if (DataName.IsEmpty())
	{
		UE_LOG(LogDNEV, Warning, TEXT("%s %s %s"), *FString(__FUNCTION__), *FString("DataName not specified : "), *DataName);
		return "";
	}

	FString dataContentDir = FString("DNEVDATA");

#if PLATFORM_ANDROID

	extern FString GExternalFilePath;
	FString dataContentDirPath = FPaths::Combine(dataContentDir, DataName);
	FString dataPath = FPaths::Combine(GExternalFilePath, dataContentDirPath);
	return dataPath;

#else

	FString contentDirAbsolute = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir());
	FString dataPath = FPaths::Combine(contentDirAbsolute, dataContentDir, DataName);
	return dataPath;

#endif
}

inline bool DoesFileExist(FString FullPath)
{
	return FPaths::FileExists(FullPath);
}

inline bool DoesFileExistInContentDirectory(FString DataPath)
{
	FString ContentPath = GetContentDNEVDataPath(DataPath);
	return DoesFileExist(ContentPath);
}

inline bool IsInGameMode(UWorld* world)
{
	if (world->WorldType == EWorldType::Type::Game ||
		world->WorldType == EWorldType::Type::GamePreview ||
		world->WorldType == EWorldType::Type::PIE)
	{
		return true;
	}

	return false;
}

inline Mvx2API::RunnerPlaybackMode PlaybackModeConvert(EPlaybackMode playbackMode)
{
	switch (playbackMode)
	{
	case EPlaybackMode::FORWARD_ONCE:			return Mvx2API::RunnerPlaybackMode::RPM_FORWARD_ONCE;
	case EPlaybackMode::FORWARD_LOOP:			return Mvx2API::RunnerPlaybackMode::RPM_FORWARD_LOOP;
	case EPlaybackMode::BACKWARD_ONCE:			return Mvx2API::RunnerPlaybackMode::RPM_BACKWARD_ONCE;
	case EPlaybackMode::BACKWARD_LOOP:			return Mvx2API::RunnerPlaybackMode::RPM_BACKWARD_LOOP;
	case EPlaybackMode::PINGPONG:				return Mvx2API::RunnerPlaybackMode::RPM_PINGPONG;
	case EPlaybackMode::PINGPONG_INVERSE:       return Mvx2API::RunnerPlaybackMode::RPM_PINGPONG_INVERSE;
	case EPlaybackMode::REALTIME:				return Mvx2API::RunnerPlaybackMode::RPM_REALTIME;
	}

	return Mvx2API::RunnerPlaybackMode::RPM_FORWARD_ONCE;
}

