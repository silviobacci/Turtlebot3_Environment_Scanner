#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <turtlebot3_environment_scanner/tb_cloud_points.h>
#include <turtlebot3_environment_scanner/tb_destination.h>
#include <geometry_msgs/Twist.h>

#define	DEG_TO_RAD	M_PI / 180
#define	RAD_TO_DEG	180 / M_PI

#define NO_VALUE	-60.0

typedef turtlebot3_environment_scanner::tb_cloud_points tb_cloud_points;

typedef turtlebot3_environment_scanner::tb_destination tb_destination;

typedef geometry_msgs::Twist twist;

extern tb_cloud_points environment;

extern tb_destination current_destination;

extern twist tb_speed;

extern bool is_automatic_mode;

void init_subscriber();

#endif
