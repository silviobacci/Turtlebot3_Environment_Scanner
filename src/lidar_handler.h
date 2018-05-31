#include <sensor_msgs/LaserScan.h>

#ifndef LIDAR_HANDLER_H
#define LIDAR_HANDLER_H

float distance = 0.0;

void lidar_callback(const sensor_msgs::LaserScan::ConstPtr& lidar);

#endif
