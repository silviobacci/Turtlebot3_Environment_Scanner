#ifndef TYPES_H
#define TYPES_H

typedef struct point {
	float x;
	float y;
	int angle;
	float distance;
} obstacle_point;

typedef struct points {
	obstacle_point obstacle[360];
	float min_distance;
	float max_distance;
} scanned_points;

#endif
