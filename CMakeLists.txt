cmake_minimum_required(VERSION 3.26)

project(Particle_System LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---------------- Dependencies ----------------
# GLFW
find_package(glfw3 CONFIG REQUIRED)

# GLEW
find_package(GLEW CONFIG REQUIRED)

# OpenGL (portable across OS)
find_package(OpenGL REQUIRED)

# ---------------- ImGui ----------------
add_library(imgui STATIC
    external/imgui/imgui.cpp
    external/imgui/imgui_draw.cpp
    external/imgui/imgui_tables.cpp
    external/imgui/imgui_widgets.cpp
    external/imgui/imgui_demo.cpp
    external/imgui/backends/imgui_impl_glfw.cpp
    external/imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
    external
    external/imgui
    external/imgui/backends
)

# ImGui needs GLFW + OpenGL
target_link_libraries(imgui PUBLIC
    glfw
    OpenGL::GL
)

# ---------------- Game ----------------
add_executable(Particle_System
    src/main.cpp
    src/stb_image.cpp
    src/Window.cpp
    src/ShaderStorageBuffer.cpp
    src/Shader.cpp
    src/Mesh.cpp
    src/Compute.cpp
 "src/Texture.cpp")


target_include_directories(Particle_System PRIVATE
    include
)

target_link_libraries(Particle_System PRIVATE
    imgui
    glfw
    GLEW::GLEW
    OpenGL::GL
)

# ---------------- Assets ----------------
add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:Particle_System>/assets
)
add_dependencies(Particle_System copy_assets)