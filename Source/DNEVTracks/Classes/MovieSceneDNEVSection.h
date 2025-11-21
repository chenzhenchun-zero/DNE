// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "MovieSceneSection.h"
#include "DNEVMeshComponent.h"
#include "Channels/MovieSceneFloatChannel.h"
#include "UObject/SoftObjectPath.h"
#include "MovieSceneDNEVSection.generated.h"

USTRUCT()
struct DNEVTRACKS_API FMovieSceneDNEVParams
{
	GENERATED_BODY()

	FMovieSceneDNEVParams();

	/** Gets the animation sequence length, not modified by play rate */
	float GetSequenceLength() const;

	UPROPERTY(EditAnywhere, Category = "DNEV")
	FString Data;

	/** The animation this section plays */
	//UPROPERTY(EditAnywhere, Category = "DNEV")
	//UDNEVMeshComponent* DNEVMeshComponent;

	/** The offset for the first loop of the animation clip */
	UPROPERTY(EditAnywhere, Category = "DNEV")
	FFrameNumber FirstLoopStartFrameOffset;

	/** The offset into the beginning of the animation clip */
	UPROPERTY(EditAnywhere, Category = "DNEV")
	FFrameNumber StartFrameOffset;

	/** The offset into the end of the animation clip */
	UPROPERTY(EditAnywhere, Category = "DNEV")
	FFrameNumber EndFrameOffset;
};

/**
 * Movie scene section that control DNEV playback
 */
UCLASS(MinimalAPI)
class UMovieSceneDNEVSection
	: public UMovieSceneSection
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Animation", meta = (ShowOnlyInnerProperties))
	FMovieSceneDNEVParams Params;

	/** Get Frame Time as Animation Time*/
	virtual float MapTimeToAnimation(float ComponentDuration, FFrameTime InPosition, FFrameRate InFrameRate) const;

protected:
	//~ UMovieSceneSection interface
	virtual TOptional<TRange<FFrameNumber> > GetAutoSizeRange() const override;
	virtual void TrimSection(FQualifiedFrameTime TrimTime, bool bTrimLeft, bool bDeleteKeys) override;
	virtual UMovieSceneSection* SplitSection(FQualifiedFrameTime SplitTime, bool bDeleteKeys) override;
	virtual void GetSnapTimes(TArray<FFrameNumber>& OutSnapTimes, bool bGetSectionBorders) const override;
	virtual TOptional<FFrameTime> GetOffsetTime() const override;

	/** ~UObject interface */
	virtual void PostLoad() override;
	virtual void Serialize(FArchive& Ar) override;

private:

	//~ UObject interface

#if WITH_EDITOR

	virtual void PreEditChange(FProperty* PropertyAboutToChange) override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	float PreviousPlayRate;

#endif

};
