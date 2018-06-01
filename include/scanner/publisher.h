#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <geometry_msgs/Twist.h>

extern geometry_msgs::Twist tb_speed;

void init_publisher();

void publish();

#endif
