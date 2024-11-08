cmake_minimum_required(VERSION 3.20)

set(JSON_LIBRARY "nlohmann"
    CACHE STRING "Select JSON library to use, valid options: nlohmann, rapidjson")

include(FetchContent)

if (JSON_LIBRARY STREQUAL "nlohmann")
FetchContent_Declare(nlohmann_json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(nlohmann_json)
elseif (JSON_LIBRARY STREQUAL "rapidjson")
FetchContent_Declare(rapid_json URL https://github.com/Tencent/rapidjson/archive/refs/tags/v1.1.0.tar.gz)
FetchContent_MakeAvailable(rapid_json)
else()
message(FATAL_ERROR "Unknown JSON_LIBRARY=${JSON_LIBRARY}")
endif()

project(Pokedex)

#Prevent DOWNLOAD_EXTRACT_TIMESTAMP warning
cmake_policy(SET CMP0135 NEW)

set(${PROJECT_NAME}_SOURCES
    "src/main.cpp"
    "src/IPokedexParser.hpp"
)

if (JSON_LIBRARY STREQUAL "nlohmann")
list(APPEND ${PROJECT_NAME}_SOURCES 
    "src/NlohmannPokedexParser.cpp"
    "src/NlohmannPokedexParser.hpp"
)
elseif (JSON_LIBRARY STREQUAL "rapidjson")
list(APPEND ${PROJECT_NAME}_SOURCES 
    "src/RapidJsonPokedexParser.cpp"
    "src/RapidJsonPokedexParser.hpp"
)
endif()

#Define Executable Target (JsonDemo.exe)
add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

#Copy Content (./content >> out/.../content)
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
            ${CMAKE_SOURCE_DIR}/content
            $<TARGET_FILE_DIR:${PROJECT_NAME}>/content)

if (JSON_LIBRARY STREQUAL "nlohmann")
target_compile_definitions(${PROJECT_NAME} PRIVATE JSON_LIBRARY_NLOHMANN)
target_link_libraries(${PROJECT_NAME} PRIVATE 
    nlohmann_json::nlohmann_json
)
elseif (JSON_LIBRARY STREQUAL "rapidjson")
target_compile_definitions(${PROJECT_NAME} PRIVATE JSON_LIBRARY_RAPIDJSON)
target_include_directories(${PROJECT_NAME} PRIVATE
    "${rapid_json_SOURCE_DIR}/include"
)
endif()
