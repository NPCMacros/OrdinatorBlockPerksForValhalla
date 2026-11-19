#include "Logging.h"

SKSEPluginLoad(const SKSE::LoadInterface* skse)
{
    try {
        OrdinatorBlockPerksForValhalla::InitializeLogging();
    } catch (const std::exception& error) {
        OrdinatorBlockPerksForValhalla::ReportStartupError(error.what());
        return false;
    }

    try {
        const auto* plugin = SKSE::PluginDeclaration::GetSingleton();
        if (!plugin || !skse) {
            spdlog::error("Plugin initialization failed: missing {}.", plugin ? "SKSE load interface" : "plugin declaration");
            return false;
        }

        const auto version = plugin->GetVersion();
        spdlog::info("Loading {} {}.{}.{}", plugin->GetName(), version.major(), version.minor(), version.patch());
        spdlog::info("Skyrim runtime: {}", skse->RuntimeVersion().string("."));
        spdlog::info("Initializing the SKSE API.");

        SKSE::Init(skse);

        spdlog::info("Plugin initialization completed successfully.");
        return true;
    } catch (const std::exception& error) {
        spdlog::error("Plugin initialization failed: {}", error.what());
        return false;
    }
}
