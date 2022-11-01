cmake_minimum_required(VERSION 3.17)

if(NOT TARGET PolymorphEngine)
    include(FetchContent)
    FetchContent_Declare(
            PolymorphEngine
            GIT_REPOSITORY https://github.com/PolymorphEngine/engine.git
            GIT_TAG feature/PluginManager
    )
    FetchContent_MakeAvailable(PolymorphEngine)

    set_target_properties(PolymorphEngine PROPERTIES POSITION_INDEPENDENT_CODE ON)
endif()