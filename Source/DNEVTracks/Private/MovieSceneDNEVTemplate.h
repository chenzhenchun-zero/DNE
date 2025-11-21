#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Evaluation/MovieSceneEvalTemplate.h"
#include "MovieSceneDNEVSection.h"
#include "MovieSceneDNEVTemplate.generated.h"

USTRUCT()
struct FMovieSceneDNEVSectionTemplateParameters : public FMovieSceneDNEVParams
{
	GENERATED_BODY()

	FMovieSceneDNEVSectionTemplateParameters() {}
	FMovieSceneDNEVSectionTemplateParameters(const FMovieSceneDNEVParams& BaseParams, FFrameNumber InSectionStartTime, FFrameNumber InSectionEndTime)
		: FMovieSceneDNEVParams(BaseParams)
		, SectionStartTime(InSectionStartTime)
		, SectionEndTime(InSectionEndTime)
	{}

	float MapTimeToAnimation(float ComponentDuration, FFrameTime InPosition, FFrameRate InFrameRate) const;

	UPROPERTY()
	FFrameNumber SectionStartTime;

	UPROPERTY()
	FFrameNumber SectionEndTime;
};

USTRUCT()
struct FMovieSceneDNEVSectionTemplate : public FMovieSceneEvalTemplate
{
	GENERATED_BODY()
	
	FMovieSceneDNEVSectionTemplate() {}
	FMovieSceneDNEVSectionTemplate(const UMovieSceneDNEVSection& Section);

	virtual UScriptStruct& GetScriptStructImpl() const override { return *StaticStruct(); }
	virtual void Evaluate(const FMovieSceneEvaluationOperand& Operand, const FMovieSceneContext& Context, const FPersistentEvaluationData& PersistentData, FMovieSceneExecutionTokens& ExecutionTokens) const override;

	UPROPERTY()
	FMovieSceneDNEVSectionTemplateParameters Params;
};
