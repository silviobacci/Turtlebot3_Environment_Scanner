#ifndef TYPES_H
#define TYPES_H

typedef struct cloud_points {
	float cloud_x[360];
	float cloud_y[360];
	float angle[360];
	float distance[360];
	float tb_x;
	float tb_y;
	float angle_min;
	float angle_max;
	float angle_increment;
	float min_distance;
	float max_distance;
} tb_cloud_points;

#endif
