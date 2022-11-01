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

include(CMake/FindPolymorphEngine.cmake)

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
target_include_directories(${PROJECT_NAME} PRIVATE
        Scripts/include
        Factory/include
        Core/include
)
target_include_directories(${PROJECT_NAME} PUBLIC
        IncludeExport
)

target_link_libraries(${PROJECT_NAME} PolymorphEngine)
set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)

if(WIN32)
    # MSVC
    target_compile_options(${PROJECT_NAME} PRIVATE /EHsc /W2 /c)
    # Set the DLLEXPORT variable to export symbols
    target_compile_definitions(${PROJECT_NAME} PRIVATE WIN_EXPORT)
endif()

include(CMake/CopyConfig.cmake)