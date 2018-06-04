#include "ros/ros.h"
#include "scanner/controller.h"
#include "scanner/subscriber.h"
#include "scanner/publisher.h"

void print_controller_info() {
	ROS_INFO("CONTROLLER INFO");
	ROS_INFO("distance %f", environment.distance[0]);
}

void run_controller() {
	//print_controller_info();

	if(environment.distance[0] < 0.5)
		tb_speed.linear.x = -0.01;

	if(environment.distance[0] == 0.0)
		tb_speed.linear.x = 0;
}
