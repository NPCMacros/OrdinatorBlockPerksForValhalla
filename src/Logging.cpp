#include "Logging.h"

#include <ShlObj.h>
#include <fstream>
#include <spdlog/sinks/ostream_sink.h>

namespace OrdinatorBlockPerksForValhalla
{
    void ReportStartupError(const char* message) noexcept
    {
        ::OutputDebugStringA("OrdinatorBlockPerksForValhalla: ");
        ::OutputDebugStringA(message);
        ::OutputDebugStringA("\n");
    }

    void InitializeLogging()
    {
        // Resolve Documents before SKSE initialization so its diagnostics reach the log.
        PWSTR documentsPath = nullptr;
        const auto result = ::SHGetKnownFolderPath(FOLDERID_Documents, KF_FLAG_DEFAULT, nullptr, &documentsPath);
        const std::unique_ptr<wchar_t, decltype(&::CoTaskMemFree)> documents(documentsPath, ::CoTaskMemFree);
        if (FAILED(result) || !documents) {
            throw std::runtime_error(fmt::format("Could not resolve Documents (HRESULT {:#010x})",
                static_cast<std::uint32_t>(result)));
        }

        const auto directory = std::filesystem::path(documents.get()) / L"My Games" / L"Skyrim Special Edition" / L"SKSE";
        std::filesystem::create_directories(directory);

        // The stream uses the native filesystem path and stays open for the lifetime of the plugin.
        static std::ofstream file;
        file.exceptions(std::ios::failbit | std::ios::badbit);
        file.open(directory / L"OrdinatorBlockPerksForValhalla.log", std::ios::out | std::ios::trunc);

        auto sink = std::make_shared<spdlog::sinks::ostream_sink_mt>(file);
        auto logger = std::make_shared<spdlog::logger>("OrdinatorBlockPerksForValhalla", std::move(sink));
        logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] %v");
        logger->flush_on(spdlog::level::info);
        logger->set_error_handler([](const std::string& message) { ReportStartupError(message.c_str()); });
        spdlog::set_default_logger(std::move(logger));
    }
}
