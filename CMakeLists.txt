project(config_reader)
cmake_minimum_required(VERSION 3.22)

add_executable(config_reader 
    src/main.cpp
    src/ConfigReader.cpp
    src/Database.cpp
)

find_package(Boost COMPONENTS filesystem program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
target_link_libraries(config_reader PRIVATE ${Boost_LIBRARIES})
