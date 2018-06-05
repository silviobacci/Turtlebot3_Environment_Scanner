#include "ros/ros.h"
#include "scanner/publisher.h"
#include "scanner/subscriber.h"

static ros::Publisher cmd_vel_publisher;
static ros::Publisher env_constructor_publisher;

geometry_msgs::Twist tb_speed;

void init_publisher(){
	ros::NodeHandle node_obj;
	cmd_vel_publisher = node_obj.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
	env_constructor_publisher = node_obj.advertise<tb_cloud_points>("/env_constructor", 1);
}

void publish_cmd_vel() {
	cmd_vel_publisher.publish(tb_speed);
}

void publish_env_constructor() {
	env_constructor_publisher.publish(environment);
}

