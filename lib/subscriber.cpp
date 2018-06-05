#include "ros/ros.h"
#include <iostream>
#include <sensor_msgs/LaserScan.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Quaternion.h>

#include "scanner/subscriber.h"
#include "scanner/publisher.h"
#include "scanner/controller.h"

#define	DEG_TO_RAD	M_PI / 180
#define	RAD_TO_DEG	180 / M_PI
#define NO_VALUE	-60

static ros::Subscriber lidar_subscriber;
static ros::Subscriber teleop_subscriber;
static ros::Subscriber env_subscriber;
static ros::Subscriber odom_subscriber;

static geometry_msgs::Point tb_position;

tb_cloud_points environment;
tb_destination current_destination;

static double quaternion_to_euler_angle(geometry_msgs::Quaternion q) {
/*
	double sinr = 2.0 * (q.w * q.x + q.y * q.z);
	double cosr = 1.0 - 2.0 * (q.x * q.x + q.y * q.y);
	roll = atan2(sinr, cosr);

	double sinp = 2.0 * (q.w * q.y - q.z * q.x);
	if (fabs(sinp) >= 1)
		pitch = copysign(M_PI / 2, sinp);
	else
		pitch = asin(sinp);

*/
	double siny = 2.0 * (q.w * q.z + q.x * q.y);
	double cosy = 1.0 - 2.0 * (q.y * q.y + q.z * q.z);  
	return atan2(siny, cosy);
}

void print_lidar_info(tb_cloud_points env) {
	ROS_INFO("RECEIVED FROM LIDAR");
}

void lidar_callback(const sensor_msgs::LaserScan::ConstPtr& lidar){
	for(int i = 0; i < 360; i++) {
		float distance = (lidar->ranges[i] >= lidar->range_min && lidar->ranges[i] <= lidar->range_max) ? lidar->ranges[i] : NO_VALUE;
		environment.cloud_x[i] = distance != NO_VALUE ? environment.tb_x + distance * cos(current_destination.tb_yaw + i * DEG_TO_RAD) : NO_VALUE;
		environment.cloud_y[i] = distance != NO_VALUE ? environment.tb_y + distance * sin(current_destination.tb_yaw + i * DEG_TO_RAD) : NO_VALUE;
	}

	publish_env_constructor();

	//print_lidar_info(environment);
}

void print_velocity_info(const geometry_msgs::Twist::ConstPtr teleop_speed) { 
	ROS_INFO("RECEIVED FROM CMD VEL"); 
} 
 
void teleop_callback(const geometry_msgs::Twist::ConstPtr& teleop_speed){ 
	tb_speed.linear.x = teleop_speed->linear.x; 
	tb_speed.angular.z = teleop_speed->angular.z; 

	//publish_cmd_vel(); 

	//print_velocity_info(teleop_speed); 
}

void odom_callback(const nav_msgs::Odometry::ConstPtr& odom){ 
	environment.tb_x = odom->pose.pose.position.x;
	environment.tb_y = odom->pose.pose.position.y;
	current_destination.tb_x = odom->pose.pose.position.x;
	current_destination.tb_y = odom->pose.pose.position.y;
	current_destination.tb_yaw = quaternion_to_euler_angle(odom->pose.pose.orientation);

	run_controller();

	publish_tb_destination();
}

void init_subscriber(){
	ros::NodeHandle node_obj;

	lidar_subscriber = node_obj.subscribe("/scan", 1, lidar_callback);
	teleop_subscriber = node_obj.subscribe("/teleop", 1, teleop_callback);
	odom_subscriber = node_obj.subscribe("/odom", 1, odom_callback);
	init_controller();
}

