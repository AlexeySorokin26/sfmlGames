cmake_minimum_required(VERSION 3.15)

# Указываем toolchain ПЕРВЫМ делом
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")

project(MySFMLProject LANGUAGES CXX)

# Включаем режим манифеста
set(VCPKG_MANIFEST_MODE ON)

# Стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ищем SFML 3.0 (без указания версии или с версией 3.0)
find_package(SFML COMPONENTS Network Graphics Window Audio System CONFIG REQUIRED)

message(STATUS "Found SFML version: ${SFML_VERSION}")

# Создаем приложение
add_executable(myapp src/main.cpp)

# Подключаем SFML (В SFML 3.0 нет SFML::System)
target_link_libraries(myapp PRIVATE
    SFML::Graphics
    SFML::Window
)

# Для отладки в Visual Studio
set_target_properties(myapp PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)