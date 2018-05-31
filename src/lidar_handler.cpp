#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include <iostream>
#include "lidar_hanlder.h"

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

