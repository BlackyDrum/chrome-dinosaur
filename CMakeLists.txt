cmake_minimum_required(VERSION 3.20)
project(Chrome-Dinosaur VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3 COMPONENTS Graphics Window System Audio REQUIRED)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics SFML::Window SFML::System SFML::Audio)

if(MSVC)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    )
endif()

if(WIN32 AND NOT SFML_STATIC_LIBRARIES)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:SFML::Graphics>"
            "$<TARGET_FILE:SFML::Window>"
            "$<TARGET_FILE:SFML::System>"
            "$<TARGET_FILE:SFML::Audio>"
            $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/assets"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
    )
endif()