cmake_minimum_required(VERSION 3.8)
project(cgx_driver)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rosidl_default_generators REQUIRED)

include_directories(
  include
  ${rclcpp_INCLUDE_DIRS}
)

# 设置动态库的搜索路径
link_directories(${PROJECT_SOURCE_DIR}/lib)

rosidl_generate_interfaces(${PROJECT_NAME}
  "srv/CgxDriverService.srv"
)

# 添加新的可执行文件
add_executable(cgx_driver_node src/cgx_driver_node.cpp)
ament_target_dependencies(cgx_driver_node rclcpp)
rosidl_get_typesupport_target(cpp_typesupport_target
  ${PROJECT_NAME} "rosidl_typesupport_cpp")
target_link_libraries(cgx_driver_node 
  CGXIZip
  cr_sdk
  LogStorageDll
  RobotConfigDll
  protobuf-c
  protobuf-rpc
  "${cpp_typesupport_target}"
  # 链接机器人 SDK 的库文件
)

# 安装可执行文件
install(TARGETS
  cgx_driver_node
  DESTINATION lib/${PROJECT_NAME}
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
