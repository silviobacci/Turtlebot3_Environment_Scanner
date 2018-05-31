#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include <iostream>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/LaserScan.h>

ros::Publisher cmd_vel_publisher;
ros::Subscriber cmd_vel_subscriber;
ros::Subscriber lidar_subscriber;
geometry_msgs::Twist twist_msg;

float distance = 0.0;

void cmd_vel_callback(const geometry_msgs::Twist::ConstPtr& msg){

	twist_msg.linear.x = msg->linear.x;
	if(distance < 0.18)
		twist_msg.linear.x = -0.01;

	if(distance == 0.0)
		twist_msg.linear.x = 0;

	twist_msg.angular.z = msg->angular.z;
	cmd_vel_publisher.publish(twist_msg);
	
	ROS_INFO("RECEIVED FROM CMD VEL");
	ROS_INFO("linear vel: %f",msg->linear.x);
	ROS_INFO("distance: %f", distance);
	ROS_INFO("output vel: %f\n", twist_msg.linear.x);
}

void lidar_callback(const sensor_msgs::LaserScan::ConstPtr& msg){
	ROS_INFO("RECEIVED FROM LIDAR");
	ROS_INFO("angle min %f", msg->angle_min);
	ROS_INFO("angle max %f", msg->angle_max);
	ROS_INFO("angle increment %f", msg->angle_increment);
	ROS_INFO("range[180] %f", msg->ranges[180]);
	ROS_INFO("intensities[180] %f\n", msg->intensities[180]);
	
	distance = msg->ranges[180];

}

int main(int argc, char **argv){
	ros::init(argc,argv,"dan_test_node");
	ros::NodeHandle node_obj;
	//ros::Subscriber number_subscriber = node_obj.subscribe("/numbers",10,number_callback);
	cmd_vel_publisher = node_obj.advertise<geometry_msgs::Twist>("/cmd_vel",1);
	cmd_vel_subscriber = node_obj.subscribe("/cmd_vel2", 1, cmd_vel_callback);
	lidar_subscriber = node_obj.subscribe("/scan", 1, lidar_callback);
	ros::spin();
	return 0;
}

