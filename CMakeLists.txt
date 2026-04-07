cmake_minimum_required(VERSION 4.2)
project(spriteAnimation)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL3 CONFIG REQUIRED)
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})
add_executable(spriteAnimation src/main.cpp)
target_link_libraries(spriteAnimation PRIVATE SDL3::SDL3)

# On Windows, copy SDL3.dll to the build directory
if(WIN32)
    add_custom_command(
            TARGET spriteAnimation POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy $<TARGET_FILE:SDL3::SDL3-shared> $<TARGET_FILE_DIR:spriteAnimation>
            VERBATIM
    )
endif()
