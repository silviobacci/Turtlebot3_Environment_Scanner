#include "ros/ros.h"
#include "scanner/publisher.h"
#include "scanner/subscriber.h"

static void print_info_message() {
	ROS_INFO("\nThis ROS node was developed by Silvio Bacci and Andrea Baldecchi in the context of the Robotics and Human Machine Interfaces exame (Master Degree in Embedded Computing Systems at the University of Pisa / Sant'Anna Schoole of Advanced Studies).\n");
}

static void init(int argc, char **argv) {
	ros::init(argc, argv, "scanner_node");
	if(argc == 3) {
		is_automatic_mode = true;
		ROS_INFO("\nWELCOME TO THE AUTOMATIC MODE OFFERED BY THE SCANNER NODE!\n");
		print_info_message();
		current_destination.final_destination_x = atof(argv[1]);
		current_destination.final_destination_y = atof(argv[2]);
		ROS_INFO("\nFINAL DESTINATION: x -> %f, y -> %f\n", current_destination.final_destination_x, current_destination.final_destination_y);
	}
	else {
		is_automatic_mode = false;
		ROS_INFO("\nWELCOME TO THE MANUAL MODE OFFERED BY THE SCANNER NODE!\n");
		print_info_message();
	}
}

int main(int argc, char **argv){
	init(argc, argv);
	init_publisher();
	init_subscriber();

	ros::spin();
	return 0;
}

