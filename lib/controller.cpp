#include "ros/ros.h"
#include "scanner/controller.h"
#include "scanner/subscriber.h"
#include "scanner/publisher.h"

void print_controller_info() {
	ROS_INFO("CONTROLLER INFO");
	ROS_INFO("distance %f", environment.obstacle[0].distance);
}

void run_controller() {
	print_controller_info();

	if(environment.obstacle[0].distance < 0.18)
		tb_speed.linear.x = -0.01;

	if(environment.obstacle[0].distance == 0.0)
		tb_speed.linear.x = 0;
}
