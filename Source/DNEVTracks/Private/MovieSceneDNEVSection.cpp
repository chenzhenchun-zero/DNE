#include "MovieSceneDNEVSection.h"
#include "MovieSceneDNEVTemplate.h"
#include "Logging/MessageLog.h"
#include "MovieScene.h"
#include "UObject/SequencerObjectVersion.h"
#include "MovieSceneTimeHelpers.h"

#define LOCTEXT_NAMESPACE "MovieSceneDNEVSection"

FMovieSceneDNEVParams::FMovieSceneDNEVParams()
{
	//DNEVMeshComponent = nullptr;
}

UMovieSceneDNEVSection::UMovieSceneDNEVSection(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	BlendType = EMovieSceneBlendType::Absolute;
	EvalOptions.EnableAndSetCompletionMode(EMovieSceneCompletionMode::ProjectDefault);

#if WITH_EDITOR

#endif
}

TOptional<FFrameTime> UMovieSceneDNEVSection::GetOffsetTime() const
{
	return TOptional<FFrameTime>(Params.FirstLoopStartFrameOffset);
}

void UMovieSceneDNEVSection::PostLoad()
{
	Super::PostLoad();

	UMovieScene* MovieSceneOuter = GetTypedOuter<UMovieScene>();

	if (!MovieSceneOuter)
	{
		return;
	}
}

void UMovieSceneDNEVSection::Serialize(FArchive& Ar)
{
	Ar.UsingCustomVersion(FSequencerObjectVersion::GUID);
	Super::Serialize(Ar);
}

FFrameNumber GetFirstLoopStartOffsetAtTrimTime(FQualifiedFrameTime TrimTime, const FMovieSceneDNEVParams& Params, FFrameNumber StartFrame, FFrameRate FrameRate)
{
	const float AnimPosition = (TrimTime.Time - StartFrame) / TrimTime.Rate;
	const float SeqLength = Params.GetSequenceLength() - FrameRate.AsSeconds(Params.StartFrameOffset + Params.EndFrameOffset);

	FFrameNumber NewOffset = FrameRate.AsFrameNumber(FMath::Fmod(AnimPosition, SeqLength));
	NewOffset += Params.FirstLoopStartFrameOffset;

	const FFrameNumber SeqLengthInFrames = FrameRate.AsFrameNumber(SeqLength);
	NewOffset = NewOffset % SeqLengthInFrames;

	return NewOffset;
}

TOptional<TRange<FFrameNumber> > UMovieSceneDNEVSection::GetAutoSizeRange() const
{
	FFrameRate FrameRate = GetTypedOuter<UMovieScene>()->GetTickResolution();
	FFrameTime AnimationLength = Params.GetSequenceLength() * FrameRate;
	int32 IFrameNumber = AnimationLength.FrameNumber.Value + (int)(AnimationLength.GetSubFrame() + 0.5f);

	return TRange<FFrameNumber>(GetInclusiveStartFrame(), GetInclusiveStartFrame() + IFrameNumber + 1);
}


void UMovieSceneDNEVSection::TrimSection(FQualifiedFrameTime TrimTime, bool bTrimLeft, bool bDeleteKeys)
{
	SetFlags(RF_Transactional);

	if (TryModify())
	{
		if (bTrimLeft)
		{
			FFrameRate FrameRate = GetTypedOuter<UMovieScene>()->GetTickResolution();

			Params.FirstLoopStartFrameOffset = HasStartFrame() ? GetFirstLoopStartOffsetAtTrimTime(TrimTime, Params, GetInclusiveStartFrame(), FrameRate) : 0;
		}

		Super::TrimSection(TrimTime, bTrimLeft, bDeleteKeys);
	}
}

UMovieSceneSection* UMovieSceneDNEVSection::SplitSection(FQualifiedFrameTime SplitTime, bool bDeleteKeys)
{
	const FFrameNumber InitialFirstLoopStartFrameOffset = Params.FirstLoopStartFrameOffset;

	FFrameRate FrameRate = GetTypedOuter<UMovieScene>()->GetTickResolution();

	const FFrameNumber NewOffset = HasStartFrame() ? GetFirstLoopStartOffsetAtTrimTime(SplitTime, Params, GetInclusiveStartFrame(), FrameRate) : 0;

	UMovieSceneSection* NewSection = Super::SplitSection(SplitTime, bDeleteKeys);
	if (NewSection != nullptr)
	{
		UMovieSceneDNEVSection* NewDNEVSection = Cast<UMovieSceneDNEVSection>(NewSection);
		NewDNEVSection->Params.FirstLoopStartFrameOffset = NewOffset;
	}

	// Restore original offset modified by splitting
	Params.FirstLoopStartFrameOffset = InitialFirstLoopStartFrameOffset;

	return NewSection;
}


void UMovieSceneDNEVSection::GetSnapTimes(TArray<FFrameNumber>& OutSnapTimes, bool bGetSectionBorders) const
{
	Super::GetSnapTimes(OutSnapTimes, bGetSectionBorders);

	const FFrameRate   FrameRate = GetTypedOuter<UMovieScene>()->GetTickResolution();
	const FFrameNumber StartFrame = GetInclusiveStartFrame();
	const FFrameNumber EndFrame = GetExclusiveEndFrame() - 1; // -1 because we don't need to add the end frame twice

	const float SeqLengthSeconds = Params.GetSequenceLength() - FrameRate.AsSeconds(Params.StartFrameOffset + Params.EndFrameOffset);
	const float FirstLoopSeqLengthInSeconds = SeqLengthSeconds - FrameRate.AsSeconds(Params.FirstLoopStartFrameOffset);

	const FFrameTime SequenceFrameLength = SeqLengthSeconds * FrameRate;
	const FFrameTime FirstLoopSequenceFrameLength = FirstLoopSeqLengthInSeconds * FrameRate;
	if (SequenceFrameLength.FrameNumber > 1)
	{
		// Snap to the repeat times
		bool IsFirstLoop = true;
		FFrameTime CurrentTime = StartFrame;
		while (CurrentTime < EndFrame)
		{
			OutSnapTimes.Add(CurrentTime.FrameNumber);
			if (IsFirstLoop)
			{
				CurrentTime += FirstLoopSequenceFrameLength;
				IsFirstLoop = false;
			}
			else
			{
				CurrentTime += SequenceFrameLength;
			}
		}
	}
}

float UMovieSceneDNEVSection::MapTimeToAnimation(float ComponentDuration, FFrameTime InPosition, FFrameRate InFrameRate) const
{
	FMovieSceneDNEVSectionTemplateParameters TemplateParams(Params, GetInclusiveStartFrame(), GetExclusiveEndFrame());
	return TemplateParams.MapTimeToAnimation(ComponentDuration, InPosition, InFrameRate);
}


#if WITH_EDITOR
void UMovieSceneDNEVSection::PreEditChange(FProperty* PropertyAboutToChange)
{
	Super::PreEditChange(PropertyAboutToChange);
}

void UMovieSceneDNEVSection::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif

float FMovieSceneDNEVParams::GetSequenceLength() const
{
	return 20.0;
	//return DNEVMeshComponent != nullptr ? DNEVMeshComponent->GetDuration() : 0.f;
}

#undef LOCTEXT_NAMESPACE 
