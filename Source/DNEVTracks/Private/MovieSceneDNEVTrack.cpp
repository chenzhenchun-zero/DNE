#include "MovieSceneDNEVTrack.h"
#include "DNEVMeshComponent.h"
#include "MovieSceneDNEVSection.h"
#include "Compilation/MovieSceneCompilerRules.h"
#include "Evaluation/MovieSceneEvaluationTrack.h"
#include "MovieSceneDNEVTemplate.h"
#include "Compilation/IMovieSceneTemplateGenerator.h"
#include "MovieScene.h"

#define LOCTEXT_NAMESPACE "MovieSceneDNEVTrack"


/* UMovieSceneDNEVTrack structors
 *****************************************************************************/

UMovieSceneDNEVTrack::UMovieSceneDNEVTrack(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#if WITH_EDITORONLY_DATA
	TrackTint = FColor(124, 15, 124, 65);
#endif

	SupportedBlendTypes.Add(EMovieSceneBlendType::Absolute);

	EvalOptions.bCanEvaluateNearestSection = true;
	EvalOptions.bEvaluateInPreroll = true;
}


/* UMovieSceneDNEVTrack interface
 *****************************************************************************/

UMovieSceneSection* UMovieSceneDNEVTrack::AddNewAnimation(FFrameNumber KeyTime, UDNEVMeshComponent* DNEVMeshComponent)
{
	UMovieSceneDNEVSection* NewSection = Cast<UMovieSceneDNEVSection>(CreateNewSection());
	{
		FFrameTime AnimationLength = DNEVMeshComponent->GetDuration()* GetTypedOuter<UMovieScene>()->GetTickResolution();
		int32 IFrameNumber = AnimationLength.FrameNumber.Value + (int)(AnimationLength.GetSubFrame() + 0.5f) + 1;
		NewSection->InitialPlacementOnRow(AnimationSections, KeyTime, IFrameNumber, INDEX_NONE);

		//NewSection->Params.DNEVMeshComponent = DNEVMeshComponent;
	}

	AddSection(*NewSection);

	return NewSection;
}


TArray<UMovieSceneSection*> UMovieSceneDNEVTrack::GetAnimSectionsAtTime(FFrameNumber Time)
{
	TArray<UMovieSceneSection*> Sections;
	for (auto Section : AnimationSections)
	{
		if (Section->IsTimeWithinSection(Time))
		{
			Sections.Add(Section);
		}
	}

	return Sections;
}

FMovieSceneEvalTemplatePtr UMovieSceneDNEVTrack::CreateTemplateForSection(const UMovieSceneSection& InSection) const
{
	return FMovieSceneDNEVSectionTemplate(*CastChecked<UMovieSceneDNEVSection>(&InSection));
}

/* UMovieSceneTrack interface
 *****************************************************************************/


const TArray<UMovieSceneSection*>& UMovieSceneDNEVTrack::GetAllSections() const
{
	return AnimationSections;
}

bool UMovieSceneDNEVTrack::SupportsType(TSubclassOf<UMovieSceneSection> SectionClass) const
{
	return SectionClass == UMovieSceneDNEVSection::StaticClass();
}

UMovieSceneSection* UMovieSceneDNEVTrack::CreateNewSection()
{
	return NewObject<UMovieSceneDNEVSection>(this, NAME_None, RF_Transactional);
}


void UMovieSceneDNEVTrack::RemoveAllAnimationData()
{
	AnimationSections.Empty();
}


bool UMovieSceneDNEVTrack::HasSection(const UMovieSceneSection& Section) const
{
	return AnimationSections.Contains(&Section);
}


void UMovieSceneDNEVTrack::AddSection(UMovieSceneSection& Section)
{
	AnimationSections.Add(&Section);
}


void UMovieSceneDNEVTrack::RemoveSection(UMovieSceneSection& Section)
{
	AnimationSections.Remove(&Section);
}

void UMovieSceneDNEVTrack::RemoveSectionAt(int32 SectionIndex)
{
	AnimationSections.RemoveAt(SectionIndex);
}

bool UMovieSceneDNEVTrack::IsEmpty() const
{
	return AnimationSections.Num() == 0;
}

#if WITH_EDITORONLY_DATA

FText UMovieSceneDNEVTrack::GetDefaultDisplayName() const
{
	return LOCTEXT("TrackName", "DNEV");
}

#endif


#undef LOCTEXT_NAMESPACE
