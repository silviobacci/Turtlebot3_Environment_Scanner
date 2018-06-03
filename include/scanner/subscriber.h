#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <turtlebot3_environment_scanner/scanned_points.h>

typedef turtlebot3_environment_scanner::scanned_points scanned_points;

extern scanned_points environment;

void init_subscriber();

#endif
