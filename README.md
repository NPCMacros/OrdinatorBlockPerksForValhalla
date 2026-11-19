# Ordinator Block Perks for Valhalla

### AI Disclaimer

This project was developed with extensive assistance from AI (OpenAI ChatGPT and Codex). AI has been used to generate and modify source code, documentation, and technical descriptions throughout development.

No AI-generated images, videos, audio, or other media assets are used in this project.

The project is maintained and tested by a human developer, who reviews and makes the final decisions regarding its implementation.

A standalone SKSE plugin for Skyrim Special Edition. The planned compatibility mod aims to integrate Ordinator's Block perks with Valhalla Combat's blocking mechanics. Version **0.1.0** initializes SKSE and writes a startup log. Gameplay features, hooks, and perk effects are planned for later versions.

## Technical structure

- `src/Plugin.cpp` contains the SKSE entry point and initialization.
- `src/Logging.cpp` and `src/Logging.h` set up startup logging with spdlog.
- `CMakeLists.txt` defines the DLL name and version. CommonLibSSE-NG uses them to generate the SKSE metadata.
- Planned modules under `src/` are `ValhallaIntegration` for block events, `TimingStreak` for blocking streaks and timeouts, `PerkIntegration` for Ordinator effects, and `Configuration` for settings. Implementations use the `OrdinatorBlockPerksForValhalla` namespace.

## Release build

The development environment includes Rider 2026.2.3.1, Visual Studio 2022 with MSVC x64 and the Windows SDK, CMake, Ninja, and vcpkg. The vcpkg manifest brings in CommonLibSSE-NG and spdlog.

In Rider, select the Visual Studio x64 toolchain and the `release` CMake preset. `VCPKG_ROOT` must be available to the CMake process. Alternatively, build from the project directory in an **x64 Native Tools Command Prompt for VS 2022** with CMake and Ninja in `PATH`.

```bat
set "VCPKG_ROOT=%LOCALAPPDATA%\Programs\vcpkg"
cmake --preset release
cmake --build build/release
```

The DLL is located at `build/release/OrdinatorBlockPerksForValhalla.dll`. The build does not deploy it automatically. For manual testing with Vortex, place the DLL under `SKSE/Plugins/` in the mod archive. Loading the plugin requires SKSE and the Address Library for the corresponding Skyrim runtime.

## Startup log

When SKSE loads the plugin, it creates `Documents\My Games\Skyrim Special Edition\SKSE\OrdinatorBlockPerksForValhalla.log`. The log records the internal plugin name, the version, the Skyrim runtime reported by SKSE, and the completion of initialization. Errors opening the log file are reported through Windows debug output.

## License

The original project code is licensed under the [BSD Zero Clause License (0BSD)](LICENSE). It may be used, modified, and redistributed, including commercially, without attribution. Third-party components retain their own licenses. See [THIRD_PARTY_NOTICES.md](THIRD_PARTY_NOTICES.md) for the original starter template notice.
