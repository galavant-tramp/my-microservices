cmake_minimum_required(VERSION 3.15)
project(cpp-microservice VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(Threads REQUIRED)

# Add executable
add_executable(microservice main.cpp)

# Link libraries
target_link_libraries(microservice PRIVATE Threads::Threads)

# Include directories
target_include_directories(microservice PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Install target
install(TARGETS microservice DESTINATION bin)
