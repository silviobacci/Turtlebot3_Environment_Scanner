#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <turtlebot3_environment_scanner/tb_cloud_points.h>
#include <turtlebot3_environment_scanner/tb_destination.h>

typedef turtlebot3_environment_scanner::tb_cloud_points tb_cloud_points;

typedef turtlebot3_environment_scanner::tb_destination tb_destination;

//#include "scanner/types.h"

extern tb_cloud_points environment;

extern tb_destination current_destination;

void init_subscriber();

#endif
