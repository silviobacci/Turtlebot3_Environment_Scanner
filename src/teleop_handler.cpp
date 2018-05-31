#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include <iostream>
#include "teleop_hanlder.h"

void print_velocity_info(const geometry_msgs::Twist::ConstPtr teleop_speed) {
	ROS_INFO("RECEIVED FROM CMD VEL");
	ROS_INFO("teleop linear vel: %f",teleop_speed->linear.x);
	ROS_INFO("teleop angular vel: %f",teleop_speed->angular.z);
	ROS_INFO("distance: %f", distance);
	ROS_INFO("output linear vel: %f\n", tb_speed.linear.x);
	ROS_INFO("output angular vel: %f\n", tb_speed.angular.z);
}

void teleop_callback(const geometry_msgs::Twist::ConstPtr& teleop_speed){
	tb_speed.linear.x = teleop_speed->linear.x;
	tb_speed.angular.z = teleop_speed->angular.z;
	
	run_controller();

	cmd_vel_publisher.publish(tb_speed);
	
	print_velocity_info(teleop_speed);
}
