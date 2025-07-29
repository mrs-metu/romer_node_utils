cmake_minimum_required(VERSION 3.8)
project(romer_node_utils)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(Eigen3 REQUIRED)
find_package(rclcpp REQUIRED)
find_package(ament_cmake REQUIRED)
find_package(std_srvs REQUIRED)
find_package(rosgraph_msgs REQUIRED)

include_directories(include ${EIGEN3_INCLUDE_DIR})

add_executable(clock_server
  src/romer_node_utils/clock_server.cpp
)

add_executable(node
  src/romer_node_utils/node.cpp
)

ament_target_dependencies(clock_server
  rclcpp
  rosgraph_msgs
  std_srvs
)

ament_target_dependencies(node
  rclcpp
  std_srvs
)

install(TARGETS
  clock_server
  node
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY include/
  DESTINATION include/
)

# Export include directories and dependencies
ament_export_include_directories(include)

ament_package()
