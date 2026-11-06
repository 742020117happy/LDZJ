cmake_minimum_required(VERSION 3.8)
project(robot_arm_control)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(control_msgs REQUIRED)
find_package(rclcpp_action REQUIRED)

find_package(std_msgs REQUIRED)


include_directories(
  include
  ${rclcpp_INCLUDE_DIRS}
)

# 设置动态库的搜索路径
link_directories(${PROJECT_SOURCE_DIR}/lib)



add_executable(moveit_controller src/moveit_controller.cpp)

add_executable(reduced_mode_monitor src/reduced_mode_monitor.cpp)
ament_target_dependencies(moveit_controller rclcpp std_msgs sensor_msgs control_msgs rclcpp_action)
ament_target_dependencies(reduced_mode_monitor
  rclcpp
  std_msgs
)

install(TARGETS
  reduced_mode_monitor
  moveit_controller
  DESTINATION lib/${PROJECT_NAME})
  
target_link_libraries(moveit_controller
  CGXIZip
  cr_sdk
  LogStorageDll
  RobotConfigDll
  protobuf-c
  protobuf-rpc
"${cpp_typesupport_target}"
)


target_link_libraries(reduced_mode_monitor
  CGXIZip
  cr_sdk
  LogStorageDll
  RobotConfigDll
  protobuf-c
  protobuf-rpc
"${cpp_typesupport_target}"
)


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
