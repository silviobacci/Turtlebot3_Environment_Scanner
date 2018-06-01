#include "ros/ros.h"
#include "scanner/publisher.h"

static ros::Publisher cmd_vel_publisher;

geometry_msgs::Twist tb_speed;

void init_publisher(){
	ros::NodeHandle node_obj;
	cmd_vel_publisher = node_obj.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
}

void publish() {
	cmd_vel_publisher.publish(tb_speed);
}

