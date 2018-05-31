#include <geometry_msgs/Twist.h>

#ifndef TELEOP_HANDLER_H
#define TELEOP_HANLDER_H

geometry_msgs::Twist tb_speed;

static void teleop_callback(const geometry_msgs::Twist::ConstPtr& teleop_speed);

#endif
