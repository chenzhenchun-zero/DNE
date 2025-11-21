#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"
#include "Stats/Stats.h"

#include <string>

/**
 * The public interface to this module
 */
class FDNEVModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/**
	 * Singleton-like access to this module's interface.  This is just for convenience!
	 * Beware of calling this during the shutdown phase, though.  Your module might have been unloaded already.
	 *
	 * @return Returns singleton instance, loading the module on demand if needed
	 */
	static inline FDNEVModule& Get()
	{
		return FModuleManager::LoadModuleChecked< FDNEVModule >("DNEV");
	}

	/**
	 * Checks to see if this module is loaded and ready.  It is only valid to call Get() if IsAvailable() returns true.
	 *
	 * @return True if the module is loaded and ready to use
	 */
	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("DNEV");
	}

private:

	void LoadDLL(FString name);
	void LoadPlugin(FString name);

	TArray<FString> DllSearchPaths;
	TArray<void*> DllHandles;

};

DECLARE_STATS_GROUP(TEXT("DNEV"), STATGROUP_DNEV, STATCAT_Advanced);