cmake_minimum_required(VERSION 3.15)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
project(MySFMLProject LANGUAGES CXX)

set(VCPKG_MANIFEST_MODE ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML COMPONENTS Network Graphics Window Audio System CONFIG REQUIRED)

message(STATUS "Found SFML version: ${SFML_VERSION}")

add_executable(myapp src/main.cpp)

target_link_libraries(myapp PRIVATE
    SFML::Graphics
    SFML::Window
)

set_target_properties(myapp PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)