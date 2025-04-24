cmake_minimum_required(VERSION 3.10)
project(OpenGL_Grafos)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable
add_executable(${PROJECT_NAME}
    src/main.cpp
    # add other source files here
)

# Include directories
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/external/glad/include
    ${PROJECT_SOURCE_DIR}/external/glfw/include
    ${PROJECT_SOURCE_DIR}/external/glm

)

# Add subdirectories (if you use git submodules or manually include GLAD/GLFW)
add_subdirectory(external/glfw)

# GLAD source
add_library(glad STATIC external/glad/src/glad.c)

# Link libraries
target_link_libraries(${PROJECT_NAME}
    glad
    glfw
    ${CMAKE_DL_LIBS}
)

# On macOS, link Cocoa, IOKit, CoreVideo
if(APPLE)
    target_link_libraries(${PROJECT_NAME}
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
endif()
