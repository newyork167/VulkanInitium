cmake_minimum_required(VERSION 2.8.12)
project(VulkanInitium)
set(CMAKE_CXX_STANDARD 17)
set(_SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING)

# CHANGEME when you want to not run in debug
set(NDEBUG TRUE)

# Set external src folder
set(CONAN_EXTERNAL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/external)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)

option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_TESTS OFF)

option(BUILD_BULLET2_DEMOS OFF)
option(BUILD_CPU_DEMOS OFF)
option(BUILD_EXTRAS OFF)
option(BUILD_OPENGL3_DEMOS OFF)
option(BUILD_UNIT_TESTS OFF)

# Run conan install based on os/arch
if(APPLE)
    execute_process( COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE ARCHITECTURE )
    if(${ARCHITECTURE} STREQUAL "arm64")
        message("Building for Apple Silicon")
        execute_process(COMMAND tools/m1.sh WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tools)
        execute_process(COMMAND conan install -if . ${CMAKE_SOURCE_DIR}/conanfile.py -e CONAN_EXTERNAL_PATH=${CONAN_EXTERNAL_PATH} --profile:build m1 --profile:host m1 --build=missing WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/)
    else()
        execute_process(COMMAND conan install -if . ${CMAKE_SOURCE_DIR}/conanfile.py -e CONAN_EXTERNAL_PATH=${CONAN_EXTERNAL_PATH} --build=missing WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/)
    endif()
else()
    message("Building for Windows/Linux")
    execute_process(COMMAND conan install -if . ${CMAKE_SOURCE_DIR}/conanfile.py -e CONAN_EXTERNAL_PATH=${CONAN_EXTERNAL_PATH} --build=missing WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/)
endif()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set_directory_properties(PROPERTIES external/ ADDITIONAL_MAKE_CLEAN_FILES)

set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})

find_package(imgui CONFIG)
find_package(glad MODULE)
find_package(glfw3 MODULE REQUIRED)
find_package(stb MODULE)
find_package(glm MODULE)
find_package(fmt MODULE)
find_package(spdlog MODULE)

# Dependencies -- Boost
Set(Boost_INSTALL_DIR ${CONAN_BOOST_ROOT})
find_package(Boost 1.79.0 COMPONENTS filesystem)

# Setup and find Vulkan SDK
if(WIN32)
    # SET VULKAN SDK PATH - Can set manually by replacing ${VULKAN_ROOTS} in set command below
    # Attempts to find the library by searching the default installation path
    file(GLOB VULKAN_ROOTS "C:/VulkanSDK/*" LIMIT_COUNT 1)
    message("VULKAN_ROOTS: ${VULKAN_ROOTS}")

    set(ENV{VULKAN_SDK} ${VULKAN_ROOTS})
    message("Vulkan SDK Path: $ENV{VULKAN_SDK}")

    find_package(Vulkan REQUIRED)
elseif(APPLE)
    find_package(moltenvk REQUIRED)
endif()

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++17")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

include_directories(include/
                    "src/")

# file(GLOB THIRD_PARTY_SOURCES "VulkanInitium/Third Party/glad/src/glad.c")
file(GLOB PROJECT_HEADERS include/*.hpp)
file(GLOB_RECURSE PROJECT_SOURCES src/*.cpp)
file(GLOB_RECURSE PROJECT_SHADERS data/*.comp
                          data/*.frag 
                          data/*.fs
                          data/*.geom
                          data/*.vert 
                          data/*.vs)
file(GLOB PROJECT_CONFIGS CMakeLists.txt
                          Readme.md
                         .gitattributes
                         .gitignore
                         .gitmodules
                         conanfile.py
                         dependencies.py)

source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Shaders" FILES ${PROJECT_SHADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Third Party" FILES ${THIRD_PARTY_SOURCES})

add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
                               ${PROJECT_SHADERS} ${PROJECT_CONFIGS}
                               ${THIRD_PARTY_SOURCES})


message("Linking ${Vulkan_LIBRARY}")
target_include_directories(${PROJECT_NAME} PUBLIC ${Vulkan_INCLUDE_DIRS})

conan_target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS}
        PRIVATE
        Boost::filesystem)
conan_target_link_libraries(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

# Copy Assets
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/data)
file(COPY ${CMAKE_CURRENT_LIST_DIR}/data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# If we are debugging, symlink the shaders directory to allow live reloading/editing
if (NDEBUG)
    set(DEBUG_SHADER_SOURCE \"${CMAKE_CURRENT_SOURCE_DIR}/data/shaders\")
    set(DEBUG_SHADER_DESTINATION \"${CMAKE_CURRENT_BINARY_DIR}/data/shaders\")

    find_package (Python3 COMPONENTS Interpreter Development REQUIRED)
    message("Python3 found for linking shaders?: ${Python3_FOUND}: ${Python3_EXECUTABLE}")

    if(Python3_FOUND)
        message("Attempting to symlink shaders for live reloading from ${DEBUG_SHADER_SOURCE} to ${DEBUG_SHADER_DESTINATION}")
        message("")
        add_custom_command(
                TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${Python3_EXECUTABLE} "${CMAKE_CURRENT_SOURCE_DIR}/tools/debug_SymlinkShaders.py"
                -s ${CMAKE_CURRENT_SOURCE_DIR}/data/shaders
                -d ${CMAKE_CURRENT_BINARY_DIR}/bin/shaders)
    else()
        message("Symlinking shaders for debug requires python 3")
    endif()
endif()
