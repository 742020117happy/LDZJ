from moveit_configs_utils import MoveItConfigsBuilder
from moveit_configs_utils.launches import generate_demo_launch
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node  # 导入Node

def generate_launch_description():
    # 声明可接收的命令行参数
    declare_velocity_factor = DeclareLaunchArgument(
        'move_group.max_velocity_scaling_factor',
        default_value='0.5',
        description='Scaling factor for velocity limits'
    )
    
    declare_acceleration_factor = DeclareLaunchArgument(
        'move_group.max_acceleration_scaling_factor',
        default_value='0.5',
        description='Scaling factor for acceleration limits'
    )
    
    # 获取参数值
    velocity_factor = LaunchConfiguration('move_group.max_velocity_scaling_factor')
    acceleration_factor = LaunchConfiguration('move_group.max_acceleration_scaling_factor')
    
    # 构建MoveIt配置
    moveit_config = MoveItConfigsBuilder(
        "multipleshapes", 
        package_name="robot_moveit_config"
    ).to_moveit_configs()
    
    # 创建自定义的move_group节点
    move_group_node = Node(
        package='moveit_ros_move_group',
        executable='move_group',
        name='move_group',
        output='screen',
        parameters=[
            moveit_config.to_dict(),
            {
                'max_velocity_scaling_factor': velocity_factor,
                'max_acceleration_scaling_factor': acceleration_factor
            }
        ]
    )
    
    # 生成标准启动描述
    demo_launch = generate_demo_launch(moveit_config)
    
    # 添加自定义节点和参数声明
    demo_launch.add_action(declare_velocity_factor)
    demo_launch.add_action(declare_acceleration_factor)
    demo_launch.add_action(move_group_node)
    
    return demo_launch