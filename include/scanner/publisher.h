#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <geometry_msgs/Twist.h>

extern geometry_msgs::Twist tb_speed;

void init_publisher();

void publish_cmd_vel();

void publish_env_constructor();

void publish_tb_destination();

#endif
