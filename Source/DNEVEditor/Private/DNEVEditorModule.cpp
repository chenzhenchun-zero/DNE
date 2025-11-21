#include "DNEVEditorModule.h"

#include "CoreMinimal.h"
#include "Settings/ProjectPackagingSettings.h"
#include "HAL/PlatformFileManager.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "Misc/Paths.h"

#include <string>

IMPLEMENT_MODULE(FDNEVEditorModule, DNEVEditor);

void FDNEVEditorModule::StartupModule()
{
	UProjectPackagingSettings* PackagingSettings = GetMutableDefault<UProjectPackagingSettings>();

	bool assetPathSet = false;
	FString DNEVDataName = FString(TEXT("DNEVDATA"));

	for (auto& stageDirs : PackagingSettings->DirectoriesToAlwaysStageAsNonUFS)
	{
		if (stageDirs.Path.ToLower() == DNEVDataName.ToLower())
		{
			assetPathSet = true;
		}
	}

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	FString contentDirPath = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir());
	FString dataPath = FPaths::Combine(contentDirPath, DNEVDataName);
	
	if (!PlatformFile.DirectoryExists(*dataPath))
		PlatformFile.CreateDirectory(*dataPath);

	if (PlatformFile.DirectoryExists(*dataPath) &&
		!assetPathSet)
	{
		//const FText MessageTitle = LOCTEXT("DNEVTitle", "DNEV");
		//const FText MessageText = LOCTEXT("DNEV", "The DNEV plugin has automatically added /Content/DNEVDATA/ to this Project's Staging Directories.");
		//FMessageDialog::Open(EAppMsgType::Ok, MessageText, &MessageTitle);

		FDirectoryPath dirPath;
		dirPath.Path = DNEVDataName;

		PackagingSettings->DirectoriesToAlwaysStageAsNonUFS.Add(dirPath);
		PackagingSettings->SaveConfig();
		PackagingSettings->UpdateDefaultConfigFile();
	}
}

void FDNEVEditorModule::ShutdownModule()
{

}
