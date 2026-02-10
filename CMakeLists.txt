cmake_minimum_required(VERSION 3.18)
cmake_policy(SET CMP0167 NEW)

project(workspacer)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED COMPONENTS json)

add_executable(workspacer
  src/main.cpp
  src/cli/cli.cpp
  src/io/io.cpp
  src/process_launcher/process_launcher.cpp
  src/filesystem/file.cpp
  src/orchestrator/orchestrator.cpp
)

target_include_directories(workspacer PRIVATE
  src
  ${Boost_INCLUDE_DIRS}
)

target_link_libraries(workspacer PRIVATE Boost::json)

