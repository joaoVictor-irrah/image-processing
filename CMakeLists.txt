cmake_minimum_required(VERSION 4.0)
project(image_processing)

set(CMAKE_CXX_STANDARD 14)

add_executable(image_processing
        src/Image.cpp
        src/main.cpp
        src/Image.h
        src/stb_image.h
        src/stb_image_write.h)

# Set working directory to project root for CLion debugger
set_target_properties(image_processing PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)
