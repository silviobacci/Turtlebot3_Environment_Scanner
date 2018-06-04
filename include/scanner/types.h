#ifndef TYPES_H
#define TYPES_H

typedef struct cloud_points {
	float x[360];
	float y[360];
	float angle[360];
	float distance[360];
	float angle_min;
	float angle_max;
	float angle_increment;
	float min_distance;
	float max_distance;
} tb_cloud_points;

#endif
