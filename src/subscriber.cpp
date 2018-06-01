#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include <sensor_msgs/LaserScan.h>
#include <iostream>

#include "scanner/subscriber.h"
#include "scanner/publisher.h"
#include "scanner/controller.h"

static ros::Subscriber lidar_subscriber;
static ros::Subscriber teleop_subscriber;

float distance;

void print_lidar_info(const sensor_msgs::LaserScan::ConstPtr lidar) {
	ROS_INFO("RECEIVED FROM LIDAR");
	ROS_INFO("angle min %f", lidar->angle_min);
	ROS_INFO("angle max %f", lidar->angle_max);
	ROS_INFO("angle increment %f", lidar->angle_increment);
	ROS_INFO("range[180] %f", lidar->ranges[180]);
	ROS_INFO("intensities[180] %f\n", lidar->intensities[180]);
}

void lidar_callback(const sensor_msgs::LaserScan::ConstPtr& lidar){
	print_lidar_info(lidar);
	
	distance = lidar->ranges[180];
}

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

	publish(); 

	print_velocity_info(teleop_speed); 
}

void init_subscriber(){
	ros::NodeHandle node_obj;

	distance = 0.0;
	lidar_subscriber = node_obj.subscribe("/scan", 1, lidar_callback);
	teleop_subscriber = node_obj.subscribe("/teleop", 1, teleop_callback);
}

