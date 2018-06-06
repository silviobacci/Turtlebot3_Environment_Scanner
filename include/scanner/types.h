#ifndef TYPES_H
#define TYPES_H

typedef struct cloud_points {
	float cloud_x[360];
	float cloud_y[360];
	float tb_x;
	float tb_y;
} tb_cloud_points;

typedef struct destination {
	float final_destination_x;
	float final_destination_y;
	float destination_x;
	float destination_y;
	float motion_state;
	float tb_x;
	float tb_y;
	float tb_yaw;
	float tb_linear_velocity;
	float tb_angular_velocity;
} tb_destination;

#endif
