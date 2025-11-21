using UnrealBuildTool;

public class DNEVSequencer : ModuleRules
{
    public DNEVSequencer(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePathModuleNames.AddRange(
            new string[] {
                "Sequencer",
            }
        );
        
        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "AssetTools",
                "Core",
                "CoreUObject",
                "EditorStyle",
                "Engine",
                "LevelSequence",
                "MovieScene",
                "MovieSceneTools",
                "MovieSceneTracks",
                "RHI",
                "Sequencer",
                "Slate",
                "SlateCore",
                "TimeManagement",
                "EditorFramework",
                "UnrealEd",
                "DNEVTracks",
                "DNEV",
            }
        );
    }
}
