cmake_minimum_required(VERSION 3.10)

# 1. Project Setup
project(MyCProject C)

# Add this near the top
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# --- Define Directories ---
# This variable stores the path to the project root (where this CMakeLists.txt is).
set(PROJECT_ROOT_DIR ${CMAKE_SOURCE_DIR})
set(SOURCE_DIR "src")
set(INCLUDE_DIR "include")
set(EXECUTABLE_NAME "my_program")
set(OUTPUT_DIR "out")

# 2. Output Configuration
# Set the final executable's output path to the project root's 'out' folder.
# This is relative to the build directory (e.g., 'build/').
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_ROOT_DIR}/${OUTPUT_DIR}")

# 3. Source File Discovery
# Finds all .c files in the src/ directory
file(GLOB SOURCE_FILES "${SOURCE_DIR}/*.c")

# Check if any source files were found
if(NOT SOURCE_FILES)
    message(FATAL_ERROR "No .c files found in the 'src/' directory. Build aborted.")
endif()

# 4. Target Definition
add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})

# Add the include directory so the compiler can find the .h files
target_include_directories(${EXECUTABLE_NAME} PUBLIC
    ${INCLUDE_DIR}
)

# 5. Optional: Set C standard
set_target_properties(${EXECUTABLE_NAME} PROPERTIES
    C_STANDARD 11
    C_STANDARD_REQUIRED ON
)
