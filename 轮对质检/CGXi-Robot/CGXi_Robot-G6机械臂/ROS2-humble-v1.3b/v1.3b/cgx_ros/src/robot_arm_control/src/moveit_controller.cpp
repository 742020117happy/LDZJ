#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/joint_state.hpp>
#include <control_msgs/action/follow_joint_trajectory.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <trajectory_msgs/msg/joint_trajectory.hpp>
#include <cmath>
#include "cgx_driver/robotapi.h"
#include "cgx_driver/basestruct.h"
#include <std_msgs/msg/bool.hpp>  // 包含布尔消息的头文件

class MoveItController : public rclcpp::Node {
public:
    MoveItController()
        : Node("moveit_controller"), reduced_mode_active_(false), robotHandle(0)   {
        // 连接机器人
        CRresult res = cr_create_robot(&robotHandle, "192.168.6.6", 2323, "123");
        if (res != sucess) {
            RCLCPP_ERROR(this->get_logger(), "Failed to connect to the robot. Error code: %d", res);
            return;
        }

        action_server_ = rclcpp_action::create_server<control_msgs::action::FollowJointTrajectory>(
            this,
            "/test_group_controller/follow_joint_trajectory", 
            std::bind(&MoveItController::handle_goal, this, std::placeholders::_1, std::placeholders::_2),
            std::bind(&MoveItController::handle_cancel, this, std::placeholders::_1),
            std::bind(&MoveItController::handle_accepted, this, std::placeholders::_1));

        publisher_ = this->create_publisher<sensor_msgs::msg::JointState>("/joint_states", 10);

        subscription_ = this->create_subscription<std_msgs::msg::Bool>(
            "/reduced_mode_state", 10,
            [this](const std_msgs::msg::Bool::SharedPtr msg) {
                reduced_mode_active_.store(msg->data);
            });

        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(100),  // 100ms 发布一次
            std::bind(&MoveItController::publishJointStates, this));

        RCLCPP_INFO(this->get_logger(), "MoveIt Controller and Joint State Publisher are ready.");
    }

private:
    rclcpp_action::GoalResponse handle_goal(
        const rclcpp_action::GoalUUID & uuid,
        std::shared_ptr<const control_msgs::action::FollowJointTrajectory::Goal> goal) {
        (void)goal; 
        RCLCPP_INFO(this->get_logger(), "Received new goal request");
        (void)uuid;
        return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
    }

    rclcpp_action::CancelResponse handle_cancel(
        const std::shared_ptr<rclcpp_action::ServerGoalHandle<control_msgs::action::FollowJointTrajectory>> goal_handle) {
        RCLCPP_INFO(this->get_logger(), "Received request to cancel goal");
        (void)goal_handle;
        return rclcpp_action::CancelResponse::ACCEPT;
    }

    void handle_accepted(const std::shared_ptr<rclcpp_action::ServerGoalHandle<control_msgs::action::FollowJointTrajectory>> goal_handle) {
        std::thread{std::bind(&MoveItController::execute, this, std::placeholders::_1), goal_handle}.detach();
    }


    void execute(const std::shared_ptr<rclcpp_action::ServerGoalHandle<control_msgs::action::FollowJointTrajectory>> goal_handle) {
        const auto goal = goal_handle->get_goal();
        auto result = std::make_shared<control_msgs::action::FollowJointTrajectory::Result>();


    
        auto trajectory = goal->trajectory;
        int point_num = trajectory.points.size();
        RCLCPP_INFO(this->get_logger(), "Number of points: %d", point_num);
        
        for (int i = 0; i <  point_num; i++) {
            const auto& print_point = trajectory.points[i];
            RCLCPP_INFO(this->get_logger(), "trajectory point %d: positions=[%f, %f, %f, %f, %f, %f]", i, print_point.positions[0], print_point.positions[1], print_point.positions[2], print_point.positions[3], print_point.positions[4], print_point.positions[5]);
        }

        int interpolation_points_per_segment = 5;

        std::vector<trajectory_msgs::msg::JointTrajectoryPoint> interpolated_points;
        for (int i = 0; i < point_num - 1; ++i) {
            const auto& start_point = trajectory.points[i];
            const auto& end_point = trajectory.points[i + 1];
            interpolated_points.push_back(start_point);

            for (int j = 1; j <= interpolation_points_per_segment; ++j) {
                double ratio = static_cast<double>(j) / (interpolation_points_per_segment + 1);
                trajectory_msgs::msg::JointTrajectoryPoint interpolated_point;
                interpolated_point.positions.resize(start_point.positions.size());
                interpolated_point.velocities.resize(start_point.velocities.size());
                interpolated_point.accelerations.resize(start_point.accelerations.size());

                for (size_t k = 0; k < start_point.positions.size(); ++k) {
                    interpolated_point.positions[k] = start_point.positions[k] + ratio * (end_point.positions[k] - start_point.positions[k]);
                    interpolated_point.velocities[k] = start_point.velocities[k] + ratio * (end_point.velocities[k] - start_point.velocities[k]);
                    interpolated_point.accelerations[k] = start_point.accelerations[k] + ratio * (end_point.accelerations[k] - start_point.accelerations[k]);
                }
                interpolated_points.push_back(interpolated_point);
            }
        }
        interpolated_points.push_back(trajectory.points.back());

        int interpolated_point_num = interpolated_points.size();
        RCLCPP_INFO(this->get_logger(), "Number of interpolated points: %d", interpolated_point_num);

        CRresult res = cr_path_action(robotHandle, 1, 2);  
        if (res != sucess) {
            RCLCPP_ERROR(this->get_logger(), "Failed to start streaming mode. Error code: %d", res);
            result->error_code = control_msgs::action::FollowJointTrajectory::Result::INVALID_GOAL;
            goal_handle->abort(result);
            return;
        }
        PathData pathData;
        pathData.pathPoints = new PathPoint[10000];
        pathData.pathPointsNum = 1;
        pathData.moveTime = 2;

        PathDownloadData pathDownloadData;
        pathDownloadData.pathPara.index = 1;
        pathDownloadData.pathPara.moveType = 0;

        RCLCPP_INFO(this->get_logger(), "redudeModeInterpNum: 0");
		int redudeModeInterpNum = 0;
        for (int i = 0; i <  interpolated_point_num-1; i++) 
		{
			
            const auto& point = interpolated_points[i];

            const bool is_reduced_mode = reduced_mode_active_.load();
            if(is_reduced_mode)
			{
				redudeModeInterpNum = 2;
			}
			else
			{
				redudeModeInterpNum = 0;
			}

			double deltaJointPose[6] = {interpolated_points[i+1].positions[0] - point.positions[0], interpolated_points[i+1].positions[1] - point.positions[1], interpolated_points[i+1].positions[2] - point.positions[2], interpolated_points[i+1].positions[3] - point.positions[3], interpolated_points[i+1].positions[4] - point.positions[4], interpolated_points[i+1].positions[5] - point.positions[5]};
			for(int redudeModeInterpCnt = 0;redudeModeInterpCnt < redudeModeInterpNum + 1; redudeModeInterpCnt++)
			{
				
				
				double target_positions[6];
				for (size_t j = 0; j < point.positions.size(); j++) 
				{
					target_positions[j] = (point.positions[j] + redudeModeInterpCnt*deltaJointPose[j]/(redudeModeInterpNum+1)) * 180.0 / M_PI;
				}
		
                RCLCPP_INFO(this->get_logger(), "Interpolated trajectory point %d: positions=[%f, %f, %f, %f, %f, %f]", i, target_positions[0], target_positions[1], target_positions[2], target_positions[3], target_positions[4], target_positions[5]);
				memcpy(pathData.pathPoints[0].jointpos, target_positions, sizeof(target_positions));
				pathDownloadData.pathData = pathData;

		
				res = cr_path_download(robotHandle, pathDownloadData);
				if (res != sucess) 
				{
					RCLCPP_ERROR(this->get_logger(), "Failed to download path point. Error code: %d", res);
					result->error_code = control_msgs::action::FollowJointTrajectory::Result::INVALID_GOAL;
					goal_handle->abort(result);
					return;
				}
		
				if (goal_handle->is_canceling()) {
					result->error_code = control_msgs::action::FollowJointTrajectory::Result::SUCCESSFUL;
					goal_handle->canceled(result);
					RCLCPP_INFO(this->get_logger(), "Goal canceled");
					return;
				}  
			}				
        }
        delete[] pathData.pathPoints;  // 释放内存
    
        res = cr_path_action(robotHandle, 1, 0);  
        if (res != sucess) {
            RCLCPP_ERROR(this->get_logger(), "Failed to stop streaming mode. Error code: %d", res);
        }
    
        result->error_code = control_msgs::action::FollowJointTrajectory::Result::SUCCESSFUL;
        goal_handle->succeed(result);
        RCLCPP_INFO(this->get_logger(), "Goal succeeded");
    }

    void publishJointStates() {
        double pos[6];
        CRresult result = cr_get_jointActualPos(robotHandle, pos);  
        if (result != sucess) {
            RCLCPP_ERROR(this->get_logger(), "Failed to get joint positions. Error code: %d", result);
            return;
        }

        std::vector<double> joint_positions(pos, pos + 6);
        for (double& angle : joint_positions) {
            angle = angle * M_PI / 180.0;
        }

        auto message = sensor_msgs::msg::JointState();
        message.header.stamp = this->now();
        message.name = {"G6_joint1", "G6_joint2", "G6_joint3", "G6_joint4", "G6_joint5", "G6_joint6"}; 
        message.position = joint_positions;
        publisher_->publish(message);
    }

    rclcpp_action::Server<control_msgs::action::FollowJointTrajectory>::SharedPtr action_server_;
    rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr publisher_;
    rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr subscription_;
    std::atomic<bool> reduced_mode_active_;
    rclcpp::TimerBase::SharedPtr timer_;
    RobotHandle robotHandle;
};

int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MoveItController>());
    rclcpp::shutdown();
    return 0;
}