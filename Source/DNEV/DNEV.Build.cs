using System;
using System.IO;
using System.Collections;
using System.Collections.Generic;
using UnrealBuildTool;

public class DNEV : ModuleRules
{
    public DNEV(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        bEnforceIWYU = false;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "ProceduralMeshComponent"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "Projects",
                "RenderCore",
                "RHI",
            }
        );

        string PLUGIN_ROOT_DIR = Path.GetFullPath(Path.Combine(ModuleDirectory, "..", ".."));
        string PROJECT_ROOT_DIR = Path.GetFullPath(Path.Combine(PLUGIN_ROOT_DIR, "..", ".."));

        string PluginLibDir = Path.Combine(PLUGIN_ROOT_DIR, "Source", "lib");
        string PluginIncludeDir = Path.Combine(PLUGIN_ROOT_DIR, "Source", "include");
        string PluginThirdPartyDir = Path.Combine(PLUGIN_ROOT_DIR, "Source", "ThirdParty");

        string ProjectDir_Binaries = Path.Combine(PROJECT_ROOT_DIR, "Binaries");

        PublicIncludePaths.Add(PluginIncludeDir);

        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            string[] StaticLibraries = new string[]
            {
                "Mvx2BasicIO.lib",
                "MVCommon.lib",
                "Mvx2.lib",
            };

            foreach (string Lib in StaticLibraries)
            {
                string FileName = Path.Combine(PluginLibDir, "Windows", "Release", Lib);
                PublicAdditionalLibraries.Add(FileName);
            }

            string[] DllDependencies = new string[]
            {
                "Mvx2.dll",
                "Mvx2BasicIO.dll",
                "Mvx2BasicIONet.dll",
                "MVX2File_mvp.dll",
                "Mvx2Net.dll",
                "RYSK.dll",
                "RYSKData_mvp.dll",
                "RYSKDecoder_mvp.dll",
                "H264_mvp.dll",
                "MVCommon.dll",
                "MVCommonNet.dll",
            };

            string SourceBinariesDir = Path.Combine(PluginThirdPartyDir, "Windows", "Release");
            string TargetBinariesDir = Path.Combine(ProjectDir_Binaries, "Win64");

            if (!Directory.Exists(TargetBinariesDir))
                Directory.CreateDirectory(TargetBinariesDir);

            foreach (string dll in DllDependencies)
            {
                string SourcePath = Path.Combine(SourceBinariesDir, dll);
                string TargetPath = Path.Combine(TargetBinariesDir, dll);

                CopyFile(SourcePath, TargetPath);

                PublicDelayLoadDLLs.Add(dll);
                RuntimeDependencies.Add(TargetPath);
            }
        }
    }

    private void CopyFile(string source, string dest)
    {
        //System.Console.WriteLine("Copying {0} to {1}", source, dest);
        //if (System.IO.File.Exists(dest))
        //{
        //    System.IO.File.SetAttributes(dest, System.IO.File.GetAttributes(dest) & ~System.IO.FileAttributes.ReadOnly);
        //}
        try
        {
            System.IO.File.Copy(source, dest, true);
        }
        catch (System.Exception ex)
        {
            System.Console.WriteLine("Failed to copy file: {0}", ex.Message);
        }
    }
}
