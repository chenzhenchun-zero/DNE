#include "MovieSceneDNEVTemplate.h"
#include "Compilation/MovieSceneCompilerRules.h"
#include "DNEVMeshComponent.h"
#include "Evaluation/MovieSceneEvaluation.h"
#include "IMovieScenePlayer.h"
#include "DNEVActor.h"

#if WITH_EDITOR
#include "MoviePipelineQueueSubsystem.h"
#endif

DECLARE_CYCLE_STAT(TEXT("DNEV Evaluate"), MovieSceneEval_DNEV_Evaluate, STATGROUP_MovieSceneEval);
DECLARE_CYCLE_STAT(TEXT("DNEV Token Execute"), MovieSceneEval_DNEV_TokenExecute, STATGROUP_MovieSceneEval);

/** Used to set Manual Tick back to previous when outside section */
struct FPreAnimatedDNEVTokenProducer : IMovieScenePreAnimatedTokenProducer
{
	virtual IMovieScenePreAnimatedTokenPtr CacheExistingState(UObject& Object) const override
	{
		struct FToken : IMovieScenePreAnimatedToken
		{
			FToken(UDNEVMeshComponent* InComponent)
			{
				// Cache this object's current update flag and animation mode
				InAssetData = InComponent->GetDataPath();
				InRenderableFrame = InComponent->GetRenderedFrameID();
				InPlaybackMode = InComponent->GetPlaybackMode();
			}

			virtual void RestoreState(UObject& ObjectToRestore, const UE::MovieScene::FRestoreStateParams& Params)
			{
				UDNEVMeshComponent* Component = CastChecked<UDNEVMeshComponent>(&ObjectToRestore);
				// Always set the playback mode before setting new data
				// as SetDataPath creates a new DNEVDataStream
				Component->SetPlaybackMode(InPlaybackMode);
				Component->SetData(InAssetData);
				Component->Pause();
				Component->ManualSeek(InRenderableFrame);
			}
			EPlaybackMode InPlaybackMode;
			FString InAssetData;
			int InRenderableFrame;
		};

		return FToken(CastChecked<UDNEVMeshComponent>(&Object));
	}
	static FMovieSceneAnimTypeID GetAnimTypeID()
	{
		return TMovieSceneAnimTypeID<FPreAnimatedDNEVTokenProducer>();
	}
};


/** A movie scene execution token that executes a DNEV Asset */
struct FDNEVExecutionToken
	: IMovieSceneExecutionToken
{
	FDNEVExecutionToken(const FMovieSceneDNEVSectionTemplateParameters &InParams):
		Params(InParams)
	{}


	static UDNEVMeshComponent* DNEVMeshComponentFromObject(UObject* BoundObject)
	{
		if (const AActor* Actor = Cast<AActor>(BoundObject))
		{
			for (UActorComponent* Component : Actor->GetComponents())
			{
				if (UDNEVMeshComponent* DNEVComp = Cast<UDNEVMeshComponent>(Component))
				{
					return DNEVComp;
				}
			}
		}
		else if (UDNEVMeshComponent* DNEVComp = Cast<UDNEVMeshComponent>(BoundObject))
		{
			return DNEVComp;
		}
		return nullptr;
	}

	/** Execute this token, operating on all objects referenced by 'Operand' */
	virtual void Execute(const FMovieSceneContext& Context, const FMovieSceneEvaluationOperand& Operand, FPersistentEvaluationData& PersistentData, IMovieScenePlayer& Player) override
	{
		MOVIESCENE_DETAILED_SCOPE_CYCLE_COUNTER(MovieSceneEval_DNEV_TokenExecute)
		if (Operand.ObjectBindingID.IsValid())
		{
			for (TWeakObjectPtr<> WeakObj : Player.FindBoundObjects(Operand))
			{
				if (UObject* Obj = WeakObj.Get())
				{
					UDNEVMeshComponent* DNEVComp = DNEVMeshComponentFromObject(Obj);
					if (DNEVComp)
					{
						Player.SavePreAnimatedState(*DNEVComp, FPreAnimatedDNEVTokenProducer::GetAnimTypeID(), FPreAnimatedDNEVTokenProducer());

						if (DNEVComp->GetDataPath() != Params.Data)
						{
							// Always set the playback mode to loop, as we don't know how long the sequencer track will be
							DNEVComp->SetPlaybackMode(EPlaybackMode::FORWARD_LOOP);
							DNEVComp->SetData(Params.Data);
						}

						// calculate the time at which to evaluate the animation
						const float EvalTime = Params.MapTimeToAnimation(DNEVComp->GetDuration(), Context.GetTime(), Context.GetFrameRate());
						const int32 EvalFrame = DNEVComp->GetFrameAtTime(EvalTime);

#if WITH_EDITOR
						if (GEditor)
						{
							const UMoviePipelineQueueSubsystem* Subsystem = GEditor->GetEditorSubsystem<UMoviePipelineQueueSubsystem>();
							
							check(Subsystem);

							if (Subsystem->IsRendering())
							{
								if (DNEVComp->IsPlaying())
									DNEVComp->Pause();

								if (DNEVComp->GetRenderedFrameID() != EvalFrame)
									DNEVComp->ManualSeek(EvalFrame);

								return;
							}
						}
#endif

						const EMovieScenePlayerStatus::Type PlayerStatus = Player.GetPlaybackStatus();

						switch (PlayerStatus)
						{
							case EMovieScenePlayerStatus::Scrubbing:
							// 	if (DNEVComp->IsPlaying())
							// 		DNEVComp->Pause();
							// 	
							// 	if (DNEVComp->GetRenderedFrameID() != EvalFrame)
							// 	 	DNEVComp->ManualSeek(EvalFrame, false);										
							// break;
						case EMovieScenePlayerStatus::Stepping:
						case EMovieScenePlayerStatus::Jumping:
						case EMovieScenePlayerStatus::Stopped:
						case EMovieScenePlayerStatus::Paused:
								if (DNEVComp->IsPlaying())
									DNEVComp->Pause();

								if (DNEVComp->GetRenderedFrameID() != EvalFrame)
									DNEVComp->ManualSeek(EvalFrame);
								break;
							case EMovieScenePlayerStatus::Playing:

								// If this isn't playing, then immediately begin playing and force
								// it to seek to the correct frame
								if (!DNEVComp->IsPlaying())
								{
									DNEVComp->Play();
									DNEVComp->Seek(EvalFrame);
								}

								if (DNEVComp->GetRenderedFrameID() > EvalFrame||
									FMath::Abs(DNEVComp->GetRenderedFrameID() - EvalFrame) > 10)
								{
									DNEVComp->Pause();
									DNEVComp->Play();
									DNEVComp->Seek(EvalFrame);
								}

								break;
							default:
								break;
						}
					}
				}
			}
		}
	}

	FMovieSceneDNEVSectionTemplateParameters Params;
};

FMovieSceneDNEVSectionTemplate::FMovieSceneDNEVSectionTemplate(const UMovieSceneDNEVSection& InSection)
	: Params(const_cast<FMovieSceneDNEVParams&> (InSection.Params), InSection.GetInclusiveStartFrame(), InSection.GetExclusiveEndFrame())
{
}

//We use a token here so we can set the manual tick state back to what it was previously when outside this section.
//This is similar to how Skeletal Animation evaluation also works.
void FMovieSceneDNEVSectionTemplate::Evaluate(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const
{
	MOVIESCENE_DETAILED_SCOPE_CYCLE_COUNTER(MovieSceneEval_DNEV_Evaluate)
	ExecutionTokens.Add(FDNEVExecutionToken(Params));
}

float FMovieSceneDNEVSectionTemplateParameters::MapTimeToAnimation(float ComponentDuration, FFrameTime InPosition, FFrameRate InFrameRate) const
{
	const float SequenceLength = ComponentDuration;
	const FFrameTime AnimationLength = SequenceLength * InFrameRate;
	const int32 LengthInFrames = AnimationLength.FrameNumber.Value + static_cast<int>(AnimationLength.GetSubFrame() + 0.5f) + 1;
	//we only play end if we are not looping, and assuming we are looping if Length is greater than default length;
	const bool bLooping = (SectionEndTime.Value - SectionStartTime.Value + StartFrameOffset + EndFrameOffset) > LengthInFrames;

	InPosition = FMath::Clamp(InPosition, FFrameTime(SectionStartTime), FFrameTime(SectionEndTime - 1));

	//const float FirstLoopSeqLength = SequenceLength - InFrameRate.AsSeconds(FirstLoopStartFrameOffset + StartFrameOffset + EndFrameOffset);
	const float SeqLength = SequenceLength - InFrameRate.AsSeconds(StartFrameOffset + EndFrameOffset);

	float AnimPosition = FFrameTime::FromDecimal((InPosition - SectionStartTime).AsDecimal()) / InFrameRate;
	AnimPosition += InFrameRate.AsSeconds(FirstLoopStartFrameOffset);
	if (SeqLength > 0.f && (bLooping || !FMath::IsNearlyEqual(AnimPosition, SeqLength, 1e-4f)))
	{
		AnimPosition = FMath::Fmod(AnimPosition, SeqLength);
	}
	AnimPosition += InFrameRate.AsSeconds(StartFrameOffset);

	return AnimPosition;
}
