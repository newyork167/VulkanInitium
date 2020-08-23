cmake_minimum_required(VERSION 3.0)
project(VulkanInitium)
set(CMAKE_CXX_STANDARD 17)

# Silences iterator warnings for C++17
set(_SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory("VulkanInitium/Third Party/glfw")

option(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_TESTS OFF)
add_subdirectory("VulkanInitium/Third Party/assimp")

option(BUILD_BULLET2_DEMOS OFF)
option(BUILD_CPU_DEMOS OFF)
option(BUILD_EXTRAS OFF)
option(BUILD_OPENGL3_DEMOS OFF)
option(BUILD_UNIT_TESTS OFF)
add_subdirectory("VulkanInitium/Third Party/bullet")

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++17")
    if(NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

include_directories(VulkanInitium/Headers/
                    "VulkanInitium/Third Party/assimp/include/"
                    "VulkanInitium/Third Party/bullet/src/"
                    "VulkanInitium/Third Party/glad/include/"
                    "VulkanInitium/Third Party/glfw/include/"
                    "VulkanInitium/Third Party/glm/"
                    "VulkanInitium/Third Party/stb/")

file(GLOB THIRD_PARTY_SOURCES "VulkanInitium/Third Party/glad/src/glad.c")
file(GLOB PROJECT_HEADERS VulkanInitium/Headers/*.hpp)
file(GLOB PROJECT_SOURCES VulkanInitium/Sources/*.cpp)
file(GLOB PROJECT_SHADERS VulkanInitium/Shaders/*.comp
                          VulkanInitium/Shaders/*.frag
                          VulkanInitium/Shaders/*.geom
                          VulkanInitium/Shaders/*.vert)
file(GLOB PROJECT_CONFIGS CMakeLists.txt
                          Readme.md
                         .gitattributes
                         .gitignore
                         .gitmodules)

source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Shaders" FILES ${PROJECT_SHADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Third Party" FILES ${THIRD_PARTY_SOURCES})

add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
                               ${PROJECT_SHADERS} ${PROJECT_CONFIGS}
                               ${THIRD_PARTY_SOURCES})
target_link_libraries(${PROJECT_NAME} assimp glfw
                      ${GLFW_LIBRARIES} ${GLAD_LIBRARIES}
                      BulletDynamics BulletCollision LinearMath)
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/VulkanInitium/Shaders $<TARGET_FILE_DIR:${PROJECT_NAME}>
    DEPENDS ${PROJECT_SHADERS})
