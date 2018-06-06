#include "ros/ros.h"
#include "scanner/controller.h"
#include "scanner/subscriber.h"
#include "scanner/publisher.h"

#define BILLION  	1000000000.0

#define SAFETY_DISTANCE	10.0

#define RADIUS_1	0.1
#define RADIUS_2	0.2
#define RADIUS_3	0.4

struct timespec start, stop;
double delta_t;

double final_destination[3];

double scalar_product(double v1[3], double v2[3]) {
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

double * vector_div(double v1[3], double v2) {
	static double sum[3];
	sum[0] = v1[0] / v2;
	sum[1] = v1[1] / v2;
	sum[2] = v1[2] / v2;

	return sum;
}

double * vector_div(double v1[3], double v2[3]) {
	static double sum[3];
	sum[0] = v1[0] / v2[0];
	sum[1] = v1[1] / v2[1];
	sum[2] = v1[2] / v2[2];

	return sum;
}

double * vector_mul(double v1[3], double v2) {
	static double sum[3];
	sum[0] = v1[0] * v2;
	sum[1] = v1[1] * v2;
	sum[2] = v1[2] * v2;

	return sum;
}

double * vector_mul(double v1[3], double v2[3]) {
	static double sum[3];
	sum[0] = v1[0] * v2[0];
	sum[1] = v1[1] * v2[1];
	sum[2] = v1[2] * v2[2];

	return sum;
}

double * vector_sum(double v1[3], double v2[3]) {
	static double sum[3];
	sum[0] = v1[0] + v2[0];
	sum[1] = v1[1] + v2[1];
	sum[2] = v1[2] + v2[2];

	return sum;
}

double * vector_diff(double v1[3], double v2[3]) {
	static double sum[3];
	sum[0] = v1[0] - v2[0];
	sum[1] = v1[1] - v2[1];
	sum[2] = v1[2] - v2[2];

	return sum;
}

double modulus(double v[3]) {
	return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

double * check_proxy_contact(double destination[3]) {
	static double * proxy_delta;

	double v_scalar;
	//double step = delta_t * tb_speed.linear.x;
	double step = 0.2;
	int num_points_r1 = 0;
	int num_points_r2 = 0;
	int num_points_r3 = 0;

	double * tmp;

	double proxy_position[3] = {environment.tb_x, environment.tb_y, 0.0};
	double proxy_normal[3] = {0.0, 0.0, 0.0};
	double * proxy_err;
	double * proxy_plane;
	double * dist_v;

	double proxy_normal_m = 0.0;
	double proxy_err_m = 0.0;
	double proxy_plane_m = 0.0;
	double dist_m = 0.0;

	for(int i = 0; i < 360; i++) {
		//compute distances of all points in the voxel
		double cloud_point[3] = {environment.cloud_x[i], environment.cloud_y[i], 0.0};
		dist_v = vector_diff(proxy_position, cloud_point);
		dist_m = modulus(dist_v);
		
		//check radiuses
		if(dist_m < RADIUS_3) {
			num_points_r3++;	
			tmp = vector_sum(proxy_normal, vector_div(dist_v, dist_m));
			proxy_normal[0] = tmp[0];
			proxy_normal[1] = tmp[1];
			proxy_normal[2] = tmp[2];
			
			if(dist_m < RADIUS_2) {
				num_points_r2++;
				
				if(dist_m < RADIUS_1)
					num_points_r1++;
			}		
		}
	}

	proxy_normal_m = modulus(proxy_normal);

	if(num_points_r3 > 0) {
		tmp = vector_div(proxy_normal, proxy_normal_m);
		proxy_normal[0] = tmp[0];
		proxy_normal[1] = tmp[1];
		proxy_normal[2] = tmp[2];
	}
	
	//free motion
	proxy_err =  vector_diff(destination, proxy_position);
	proxy_err_m = modulus(proxy_err);
	
	//compute proxy plane
	v_scalar = scalar_product(proxy_err, proxy_normal);
	proxy_plane = vector_diff(proxy_err, vector_mul(proxy_normal, v_scalar));
	proxy_plane_m = modulus(proxy_plane);
	
	// free motion
	if(proxy_err_m > step)
		proxy_delta = vector_mul(proxy_err, step/proxy_err_m); 
	else 
		proxy_delta = vector_mul(proxy_err, 1);
	
	current_destination.motion_state = 1;

	// entrched
	if(num_points_r1 > 0) {
		proxy_delta = vector_mul(proxy_normal, step / proxy_normal_m);
		current_destination.motion_state = 3;
	}
	else if(num_points_r2 > 0) {
		current_destination.motion_state = 2;
		if(v_scalar < 0){	
			if(proxy_plane_m > step)
				proxy_delta = vector_mul(proxy_plane, step / proxy_plane_m);
			else
				proxy_delta = vector_mul(proxy_plane, 1);
		}	
	}
	
	return proxy_delta;
}

void print_controller_info(double * destination) {
	ROS_INFO("CONTROLLER INFO");
	ROS_INFO("delta_t %f", delta_t);
	ROS_INFO("destination.x %f", destination[0]);
	ROS_INFO("destination.y %f", destination[1]);
	ROS_INFO("destination.z %f", destination[2]);
	ROS_INFO("tb_speed.linear.x %f", tb_speed.linear.x);
	ROS_INFO("tb_speed.linear.y %f", tb_speed.linear.y);
	ROS_INFO("tb_speed.linear.z %f", tb_speed.linear.z);
}

void init_controller() {
	clock_gettime(CLOCK_MONOTONIC, &start);
	current_destination.final_destination_x = 1.5;
	current_destination.final_destination_y = 1.0;
	final_destination[0] = current_destination.final_destination_x;
	final_destination[1] = current_destination.final_destination_y;
	final_destination[2] = 0.0;
}

void run_controller() {
	/*
	//print_controller_info();

	if(abs(environment.distance[0]) < 0.5)
		tb_speed.linear.x = -0.01;

	if(abs(environment.distance[0]) == 0.0)
		tb_speed.linear.x = 0;
	
	*/
	clock_gettime(CLOCK_MONOTONIC, &stop);
	delta_t = (stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec) / BILLION;
	clock_gettime(CLOCK_MONOTONIC, &start);

	double destination[3] = {0.0, 0.0, 0.0};

	/*
	if(tb_speed.linear.x != 0.0) {
		destination[0] = environment.tb_x + SAFETY_DISTANCE * cos(yaw);
		destination[1] = environment.tb_y + SAFETY_DISTANCE * sin(yaw);
		destination[2] = 0.0;
	}
	*/

	//print_controller_info(destination);

	double * proxy_delta = check_proxy_contact(final_destination);
	//ROS_INFO("proxy_delta.x %f", proxy_delta[0]);
	//ROS_INFO("proxy_delta.y %f", proxy_delta[1]);
	current_destination.destination_x = current_destination.tb_x + proxy_delta[0];
	current_destination.destination_y = current_destination.tb_y + proxy_delta[1];
}
