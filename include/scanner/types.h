#ifndef TYPES_H
#define TYPES_H

typedef struct cloud_points {
	float cloud_x[360];
	float cloud_y[360];
	float tb_x;
	float tb_y;
} tb_cloud_points;

typedef struct destination {
	float destination_x;
	float destination_y;
	float tb_x;
	float tb_y;
	float tb_yaw;
} tb_destination;

#endif
