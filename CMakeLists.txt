cmake_minimum_required(VERSION 3.25)
project(Particles)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
        main.cpp

        src/particles.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC
        old_src
        ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} PUBLIC
        ${SDL2_LIBRARIES}
)

# Sets executable folder to bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)