cmake_minimum_required(VERSION 3.10)
project(TradingPatterns)

set(CMAKE_CXX_STANDARD 17)

# Usando pkg-config para Pistache
find_package(PkgConfig REQUIRED)
pkg_check_modules(PISTACHE REQUIRED libpistache)

include_directories(${PISTACHE_INCLUDE_DIRS})
link_directories(${PISTACHE_LIBRARY_DIRS})

add_executable(api src/main.cpp src/api/Api.cpp)

target_link_libraries(api ${PISTACHE_LIBRARIES})
