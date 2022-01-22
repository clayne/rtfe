#include "Logging.h"

#if defined(SKYRIMAE)

	extern "C" DLLEXPORT constinit auto SKSEPlugin_Version =
		[]() {
			SKSE::PluginVersionData v{};
			v.pluginVersion = Version::MAJOR;
			v.PluginName(Version::PROJECT);
			v.AuthorName("doodlez"sv);
			v.UsesAddressLibrary(true);
			return v;
	}();

#else

	#if defined(SKYRIMVR)
		#define RUNTIME RUNTIME_VR_1_4_15_1
	#else
		#define RUNTIME RUNTIME_1_5_97
	#endif

	extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Query(const SKSE::QueryInterface* a_skse, SKSE::PluginInfo* a_info)
	{
		Logging::InitLogger();

		a_info->infoVersion = SKSE::PluginInfo::kVersion;
		a_info->name = Version::PROJECT.data();
		a_info->version = Version::MAJOR;

		if (a_skse->IsEditor()) {
			logger::critical("Loaded in editor, marking as incompatible"sv);
			return false;
		}

		const auto ver = a_skse->RuntimeVersion();
		if (ver != SKSE::RUNTIME) {
			logger::critical(FMT_STRING("Unsupported runtime version {}"sv), ver.string());
			return false;
		}

		return true;
	}
	
#endif

extern "C" DLLEXPORT bool SKSEAPI SKSEPlugin_Load(const SKSE::LoadInterface* a_skse)
{
#ifndef NDEBUG
	while (!IsDebuggerPresent()) {}
#endif

	Logging::InitLogger();

	logger::info("{} loaded"sv, Version::PROJECT);

	SKSE::Init(a_skse);


	return true;
}
