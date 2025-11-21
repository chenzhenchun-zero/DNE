#include "DNEVTracksModule.h"
#if WITH_EDITOR
#include "DNEVSequencerModule.h"
#endif // WITH_EDITOR

IMPLEMENT_MODULE(FDNEVTracksModule, DNEVTracks)

void FDNEVTracksModule::StartupModule()
{
#if WITH_EDITOR
	FDNEVSequencerModule& Module = FModuleManager::LoadModuleChecked<FDNEVSequencerModule>(TEXT("DNEVSequencer"));
#endif
}

void FDNEVTracksModule::ShutdownModule()
{
}
