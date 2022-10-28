cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 23)
set(EXECUTABLE_OUTPUT_PATH ../)

project(plugin-template)
set(NAMESPACE polymorph)

if (${CMAKE_SOURCE_DIR} EQUAL ${PROJECT_NAME})
    set(LIBRARY_OUTPUT_PATH  ../)
else()
    set(LIBRARY_OUTPUT_PATH  ${CMAKE_SOURCE_DIR}/Plugins/${PROJECT_NAME})
endif()

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






file(GLOB_RECURSE SCRIPTS_SRC Scripts/src/*.cpp)
file(GLOB_RECURSE SCRIPTS_ICL Scripts/include/*.hpp)

file(GLOB_RECURSE FACTORY_SRC Factory/src/*.cpp)
file(GLOB_RECURSE FACTORY_ICL Factory/include/*.hpp)

file(GLOB_RECURSE CORE_SRC Core/src/*.cpp)
file(GLOB_RECURSE CORE_ICL Core/include/*.hpp)
file(GLOB_RECURSE EXPORTS IncludeExport/*.hpp)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(${PROJECT_NAME} SHARED ${SCRIPTS_SRC} ${SCRIPTS_ICL} ${FACTORY_SRC} ${FACTORY_ICL} ${CORE_SRC} ${CORE_ICL} ${EXPORTS})
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES PREFIX "")
target_include_directories(${PROJECT_NAME} PUBLIC
        Scripts/include
        Factory/include
        Core/include
        IncludeExport
)

target_link_libraries(${PROJECT_NAME} PolymorphEngine)
set_target_properties(PolymorphEngine PROPERTIES EXCLUDE_FROM_ALL True POSITION_INDEPENDENT_CODE ON)
set_target_properties(${PROJECT_NAME} PROPERTIES EXCLUDE_FROM_ALL True POSITION_INDEPENDENT_CODE ON)

if(WIN32)
    # MSVC
    target_compile_options(${PROJECT_NAME} PRIVATE /EHsc /W2 /c)
    # Set the DLLEXPORT variable to export symbols
    target_compile_definitions(${PROJECT_NAME} PRIVATE WIN_EXPORT)
endif()


if (NOT "${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}")
    if (NOT EXISTS "${CMAKE_SOURCE_DIR}/Plugins/")
        file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/Plugins/")
    endif()
    if (NOT EXISTS "${CMAKE_SOURCE_DIR}/Plugins/${PROJECT_NAME}")
        file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/Plugins/${PROJECT_NAME}/")
    elseif (EXISTS "${CMAKE_SOURCE_DIR}/Plugins/${PROJECT_NAME}")
        file(REMOVE_RECURSE "${CMAKE_SOURCE_DIR}/Plugins/${PROJECT_NAME}/")
        file(MAKE_DIRECTORY "${CMAKE_SOURCE_DIR}/Plugins/${PROJECT_NAME}/")
    endif()
    file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/Assets" DESTINATION "${CMAKE_SOURCE_DIR}/Plugins/${PROJECT_NAME}")
    file(COPY_FILE "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.pcf.plugin" "${CMAKE_SOURCE_DIR}/Plugins/${PROJECT_NAME}/${PROJECT_NAME}.pcf.plugin")
    file(COPY_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md" "${CMAKE_SOURCE_DIR}/Plugins/${PROJECT_NAME}/README.md")
elseif(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.pcf.plugin")
    file(RENAME plugin-template.pcf.plugin ${PROJECT_NAME}.pcf.plugin RESULT 0)
    file(RENAME IncludeExport/polymorph IncludeExport/${NAMESPACE} RESULT 0)
    file(RENAME IncludeExport/polymorph/plugin-template.hpp IncludeExport/${NAMESPACE}/${PROJECT_NAME}.hpp RESULT 0)
endif()