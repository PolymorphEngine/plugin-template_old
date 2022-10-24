cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 23)
set(EXECUTABLE_OUTPUT_PATH ../)
set(LIBRARY_OUTPUT_PATH  ../)



project(plugin-template)
set(NAMESPACE Polymorph)


#set(CMAKE_MODULE /usr/bin/clang)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=memory")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize-memory-track-origins -fsanitize=memory -fsanitize-recover=all -fPIE -pie -fno-omit-frame-pointer  -fno-optimize-sibling-calls -O1")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")




if(NOT TARGET PolymorphEngine)
    include(FetchContent)

    FetchContent_Declare(
            PolymorphEngine
            GIT_REPOSITORY git@github.com:PolymorphEngine/engine.git
            GIT_TAG feature/PluginManager
    )

    FetchContent_MakeAvailable(PolymorphEngine)
endif()


if (NOT EXISTS "../${PROJECT_NAME}.pcf.plugin")
    file(RENAME plugin-template.pcf.plugin ${PROJECT_NAME}.pcf.plugin RESULT 0)
    file(RENAME IncludeExport/Polymorph/plugin-template.hpp IncludeExport/${NAMESPACE}/${PROJECT_NAME}.hpp RESULT 0)
endif()


file(GLOB_RECURSE SCRIPTS_SRC Scripts/src/*.cpp)
file(GLOB_RECURSE SCRIPTS_ICL Scripts/include/*.hpp)

file(GLOB_RECURSE FACTORY_SRC Factory/src/*.cpp)
file(GLOB_RECURSE FACTORY_ICL Factory/include/*.hpp)

file(GLOB_RECURSE CORE_SRC Core/src/*.cpp)
file(GLOB_RECURSE CORE_ICL Core/include/*.hpp)

add_library(${PROJECT_NAME} SHARED ${SCRIPTS_SRC} ${SCRIPTS_ICL} ${FACTORY_SRC} ${FACTORY_ICL} ${CORE_SRC} ${CORE_ICL})
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES PREFIX "")
target_include_directories(${PROJECT_NAME} PUBLIC
        Scripts/include
        Factory/include
        Core/include
        IncludeExport
)

target_link_libraries(${PROJECT_NAME} PolymorphEngine)
set_target_properties(PolymorphEngine PROPERTIES EXCLUDE_FROM_ALL True POSITION_INDEPENDENT_CODE ON)



