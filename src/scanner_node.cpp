#include "ros/ros.h"
#include "scanner/publisher.h"
#include "scanner/subscriber.h"

void init(int argc, char **argv) {
	ros::init(argc, argv, "scanner_node");
}

int main(int argc, char **argv){
	init(argc, argv);
	init_publisher();
	init_subscriber();

	ros::spin();
	return 0;
}

