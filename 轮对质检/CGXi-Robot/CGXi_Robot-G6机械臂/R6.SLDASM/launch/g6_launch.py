import os

from launch import LaunchDescription
from launch.actions import (
    DeclareLaunchArgument,
    IncludeLaunchDescription,
    ExecuteProcess,
)
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
from launch.launch_description_sources import PythonLaunchDescriptionSource
import xacro

def generate_launch_description():
    this_package = "my_robot_description"
    this_pkg_share = get_package_share_directory(this_package)

    use_sim_time = LaunchConfiguration("use_sim_time", default="true")
    robot_name = LaunchConfiguration("robot_name", default="multipleshapes")

    urdf_file = os.path.join(this_pkg_share, "urdf", "robot.urdf.xacro")
    doc = xacro.parse(open(urdf_file))
    xacro.process_doc(doc)
    robot_description = doc.toxml()

    gazebo_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(get_package_share_directory("gazebo_ros"), "launch", "gazebo.launch.py")
        ),
    )

    robot_state_publisher = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        name="robot_state_publisher",
        output="screen",
        parameters=[{"use_sim_time": use_sim_time, "robot_description": robot_description}],
    )

    spawn_entity = Node(
        package="gazebo_ros",
        executable="spawn_entity.py",
        arguments=[
            "-entity", robot_name,
            "-topic", "robot_description",
            "-x", "0.0", "-y", "0.0", "-z", "0.05",  # 初始位置
            "-R", "0.0", "-P", "0.0", "-Y", "0.0",   # 初始姿态
        ],
        output="screen",
    )

    start_arm_controller = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["test_group_controller", "--controller-manager", "/controller_manager"],
        output="screen",
    )

    start_joint_state_broadcaster = Node(
        package="controller_manager",
        executable="spawner",
        arguments=["joint_state_broadcaster", "--controller-manager", "/controller_manager"],
        output="screen",
    )

    ld = LaunchDescription()

    ld.add_action(gazebo_launch)
    ld.add_action(robot_state_publisher)
    ld.add_action(spawn_entity)
    ld.add_action(start_joint_state_broadcaster)
    ld.add_action(start_arm_controller)

    return ld