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
double roll, pitch, yaw;

static void quaternion_to_euler_angle(geometry_msgs::Quaternion q) {
	double sinr = 2.0 * (q.w * q.x + q.y * q.z);
	double cosr = 1.0 - 2.0 * (q.x * q.x + q.y * q.y);
	roll = atan2(sinr, cosr);

	double sinp = 2.0 * (q.w * q.y - q.z * q.x);
	if (fabs(sinp) >= 1)
		pitch = copysign(M_PI / 2, sinp);
	else
		pitch = asin(sinp);


	double siny = 2.0 * (q.w * q.z + q.x * q.y);
	double cosy = 1.0 - 2.0 * (q.y * q.y + q.z * q.z);  
	yaw = atan2(siny, cosy);
}

void print_lidar_info(tb_cloud_points env) {
	ROS_INFO("RECEIVED FROM LIDAR");
	ROS_INFO("distance[0] %f", env.distance[0]);
	ROS_INFO("distance[90] %f", env.distance[90]);
	ROS_INFO("distance[180] %f", env.distance[180]);
	ROS_INFO("distance[270] %f", env.distance[270]);
	ROS_INFO("min_distance %f", env.min_distance);
	ROS_INFO("max_distance %f\n", env.max_distance);
}

void lidar_callback(const sensor_msgs::LaserScan::ConstPtr& lidar){
	environment.angle_min = round(lidar->angle_min * RAD_TO_DEG);
	environment.angle_max = round(lidar->angle_max * RAD_TO_DEG);
	environment.angle_increment = round(lidar->angle_increment * RAD_TO_DEG);
	
	environment.min_distance = lidar->range_min;
	environment.max_distance = lidar->range_max;

	for(int i = 0; i < (environment.angle_max - environment.angle_min) / environment.angle_increment; i++) {
		environment.angle[i] = i * environment.angle_increment;
		environment.distance[i] = (lidar->ranges[i] >= environment.min_distance && lidar->ranges[i] <= environment.max_distance) ? lidar->ranges[i] : NO_VALUE;
		environment.cloud_x[i] = environment.distance[i] != NO_VALUE ? environment.tb_x + environment.distance[i] * cos(yaw + environment.angle[i] * DEG_TO_RAD) : NO_VALUE;
		environment.cloud_y[i] = environment.distance[i] != NO_VALUE ? environment.tb_y + environment.distance[i] * sin(yaw + environment.angle[i] * DEG_TO_RAD) : NO_VALUE;
	}

	publish_env_constructor();

	//print_lidar_info(environment);
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

	publish_cmd_vel(); 

	//print_velocity_info(teleop_speed); 
}

void odom_callback(const nav_msgs::Odometry::ConstPtr& odom){ 
	environment.tb_x = odom->pose.pose.position.x;
	environment.tb_y = odom->pose.pose.position.y;
	quaternion_to_euler_angle(odom->pose.pose.orientation);
}

void init_subscriber(){
	ros::NodeHandle node_obj;

	lidar_subscriber = node_obj.subscribe("/scan", 1, lidar_callback);
	teleop_subscriber = node_obj.subscribe("/teleop", 1, teleop_callback);
	odom_subscriber = node_obj.subscribe("/odom", 1, odom_callback);
	init_controller();
}

