#include "DNEVModule.h"

#include "DNEVPrivatePCH.h"
#include "Mvx2API/utils/PluginsLoader.h"
#include "Utils.h"

#include "HAL/FileManager.h"
#include "HAL/PlatformProcess.h"
#include "Interfaces/IPluginManager.h"
#include "Modules/ModuleManager.h"

DEFINE_LOG_CATEGORY(LogDNEV);

#define LOCTEXT_NAMESPACE "FDNEVModule"

void FDNEVModule::StartupModule()
{
#if WITH_EDITOR
	FString RelativePath = IPluginManager::Get().FindPlugin("DNEV")->GetBaseDir();
	FString FullPath = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*RelativePath);

#if PLATFORM_WINDOWS
	DllSearchPaths.Add(FPaths::Combine(FullPath, TEXT("Source/ThirdParty/Windows/Release")));
#endif
#else
	DllSearchPaths.Add(FPlatformProcess::BaseDir());
#endif

#if PLATFORM_WINDOWS
	LoadDLL("MVCommon.dll");
	LoadDLL("MVCommonNet.dll");
	LoadDLL("Mvx2.dll");
	LoadDLL("Mvx2BasicIO.dll");
	LoadDLL("Mvx2BasicIONet.dll");
	LoadDLL("Mvx2Net.dll");
	LoadDLL("RYSK.dll");
	LoadPlugin("H264_mvp.dll");
	LoadPlugin("MVX2File_mvp.dll");
	LoadPlugin("RYSKData_mvp.dll");
	LoadPlugin("RYSKDecoder_mvp.dll");
#endif
}

void FDNEVModule::ShutdownModule()
{
	for (void* handle : DllHandles)
	{
		check(handle != nullptr);
		FPlatformProcess::FreeDllHandle(handle);
	}
}

void FDNEVModule::LoadDLL(FString Name)
{
	for (const FString& path : DllSearchPaths)
	{
		FString dllPath = *FPaths::Combine(*path, *Name);
		void* dll = FPlatformProcess::GetDllHandle(*dllPath);

		if (dll != nullptr)
		{
			DllHandles.Add(dll);
		}
	}
}

void FDNEVModule::LoadPlugin(FString Name)
{
	for (const FString& path : DllSearchPaths)
	{
		FString dllPath = *FPaths::Combine(*path, *Name);
		Mvx2API::PluginsLoader::LoadPlugin((std::string(TCHAR_TO_UTF8(*dllPath)).c_str()));
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FDNEVModule, DNEV)