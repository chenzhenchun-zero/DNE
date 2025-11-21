using UnrealBuildTool;

public class DNEVTracks : ModuleRules
{
    public DNEVTracks(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "DNEV",
                "MovieRenderPipelineCore",
            }
        );


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "AnimGraphRuntime",
                "Core",
                "CoreUObject",
                "Engine",
                "TimeManagement",
            }
        );

        PublicIncludePathModuleNames.Add("TargetPlatform");

        if (Target.bBuildEditor)
        {
            PublicIncludePathModuleNames.Add("DNEVSequencer");
            DynamicallyLoadedModuleNames.Add("DNEVSequencer");

            PublicDependencyModuleNames.AddRange(
                new string[]
                {
                    "MovieScene",
                    "MovieRenderPipelineEditor",
                    "EditorSubsystem",
                }
            );

            PrivateDependencyModuleNames.AddRange(
                new string[]
                {
                    "UnrealEd",
                }
            );
        }
    }
}
