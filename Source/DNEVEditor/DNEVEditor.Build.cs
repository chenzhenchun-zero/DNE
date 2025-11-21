using UnrealBuildTool;

public class DNEVEditor : ModuleRules
{
    public DNEVEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "Projects",
                "DeveloperToolSettings",
                "PropertyEditor",
                "Slate",
                "SlateCore",
                "RHI",
                "EditorFramework",
                "UnrealEd",
            }
        );
    }
}
