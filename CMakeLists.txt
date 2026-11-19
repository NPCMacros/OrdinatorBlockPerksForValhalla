cmake_minimum_required(VERSION 3.21)

project(OrdinatorBlockPerksForValhalla VERSION 0.1.0 LANGUAGES CXX)

find_package(CommonLibSSE CONFIG REQUIRED)
add_commonlibsse_plugin(${PROJECT_NAME}
    SOURCES
        src/Plugin.cpp
        src/Logging.cpp
        src/Logging.h
)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
target_precompile_headers(${PROJECT_NAME} PRIVATE PCH.h)
target_link_libraries(${PROJECT_NAME} PRIVATE shell32 ole32)
