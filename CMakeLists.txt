# Cmake version
cmake_minimum_required(VERSION 3.10)

# Project name
project(TradingPatterns)

# CPP version
set(CMAKE_CXX_STANDARD 17)

# Reference to IDE
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Headers
include_directories(${PROJECT_SOURCE_DIR}/include)

# Pistache
find_package(PkgConfig REQUIRED)
pkg_check_modules(PISTACHE REQUIRED libpistache)
include_directories(${PISTACHE_INCLUDE_DIRS})
link_directories(${PISTACHE_LIBRARY_DIRS})

# PostegreSQL
find_package(PostgreSQL REQUIRED)
include_directories(${PostgreSQL_INCLUDE_DIRS})
link_directories(${PostgreSQL_LIBRARY_DIRS})

# RapidJSON
include_directories(/usr/include/rapidjson)


# Executable
file (GLOB_RECURSE SOURCES src/*.cpp src/controllers/*.cpp)
add_executable( api ${SOURCES})

# Link
target_link_libraries(
    api 
    ${PISTACHE_LIBRARIES}
    ${PostgreSQL_LIBRARIES}    
)
