#include "ros/ros.h"
#include <iostream>
#include <sensor_msgs/LaserScan.h>

#include "scanner/subscriber.h"
#include "scanner/publisher.h"
#include "scanner/controller.h"

#define	DEG_TO_RAD	M_PI / 180
#define	RAD_TO_DEG	180 / M_PI

static ros::Subscriber lidar_subscriber;
static ros::Subscriber teleop_subscriber;

scanned_points environment;

void print_lidar_info() {
	ROS_INFO("RECEIVED FROM LIDAR");
	ROS_INFO("distance[0] %f", environment.obstacle[0].distance);
	ROS_INFO("distance[90] %f", environment.obstacle[90].distance);
	ROS_INFO("distance[180] %f", environment.obstacle[180].distance);
	ROS_INFO("distance[270] %f", environment.obstacle[270].distance);
	ROS_INFO("min_distance %f", environment.min_distance);
	ROS_INFO("max_distance %f\n", environment.max_distance);
}

void lidar_callback(const sensor_msgs::LaserScan::ConstPtr& lidar){
	environment.min_distance = lidar->range_min;
	environment.max_distance = lidar->range_max;

	for(int i = 0; i < 360; i++) {
		environment.obstacle[i].angle = i;
		environment.obstacle[i].distance = lidar->ranges[i];
		environment.obstacle[i].x = environment.obstacle[i].distance * sin(environment.obstacle[i].angle * DEG_TO_RAD);
		environment.obstacle[i].y = environment.obstacle[i].distance * cos(environment.obstacle[i].angle * DEG_TO_RAD);
	}

	print_lidar_info();
}

void print_velocity_info(const geometry_msgs::Twist::ConstPtr teleop_speed) { 
	ROS_INFO("RECEIVED FROM CMD VEL"); 
	ROS_INFO("teleop linear vel: %f",teleop_speed->linear.x); 
	ROS_INFO("teleop angular vel: %f",teleop_speed->angular.z); 
	ROS_INFO("output linear vel: %f", tb_speed.linear.x); 
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

	lidar_subscriber = node_obj.subscribe("/scan", 1, lidar_callback);
	teleop_subscriber = node_obj.subscribe("/teleop", 1, teleop_callback);
}

