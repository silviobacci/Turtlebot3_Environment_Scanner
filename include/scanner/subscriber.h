#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <turtlebot3_environment_scanner/tb_cloud_points.h>
//#include "scanner/types.h"

typedef turtlebot3_environment_scanner::tb_cloud_points tb_cloud_points;

extern tb_cloud_points environment;

extern double roll, pitch, yaw;

void init_subscriber();

#endif
