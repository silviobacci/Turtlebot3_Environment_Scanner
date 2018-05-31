#include "teleop_handler.h"
#include "lidar_handler.h"
#include "controller.h"
#include "ros/ros.h"


ros::Publisher cmd_vel_publisher;
ros::Subscriber cmd_teleop_subscriber;
ros::Subscriber lidar_subscriber;

int main(int argc, char **argv){
	ros::init(argc, argv, "scanner_node");
	ros::NodeHandle node_obj;

	cmd_vel_publisher = node_obj.advertise<geometry_msgs::Twist>("/cmd_vel",1);

	cmd_teleop_subscriber = node_obj.subscribe("/cmd_teleop", 1, teleop_callback);
	lidar_subscriber = node_obj.subscribe("/scan", 1, lidar_callback);
	ros::spin();
	return 0;
}

