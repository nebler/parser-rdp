cmake_minimum_required(VERSION 3.10)

# Project name and version
project(MyLang VERSION 1.0 LANGUAGES CXX C)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find LLVM package
find_package(LLVM REQUIRED CONFIG)

# Set LLVM include directories and compile options
include_directories(SYSTEM ${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Automatically find all source files
file(GLOB_RECURSE SRCS
    "./src/backend/main.cpp"
)

# Define the executable
add_executable(${PROJECT_NAME} ${SRCS})

# Link LLVM libraries
llvm_map_components_to_libnames(LLVM_LIBS core orcjit native)
target_link_libraries(${PROJECT_NAME} ${LLVM_LIBS} ${LLVM_SYSTEM_LIBS} "-L/opt/homebrew/Cellar/zstd/1.5.6/lib")
# Enable assertions in debug mode
target_compile_definitions(${PROJECT_NAME} PRIVATE "$<$<CONFIG:DEBUG>:_DEBUG>")

# Enable testing
enable_testing()

# Define a test
add_test(NAME ExampleTest COMMAND ${PROJECT_NAME} --version)
