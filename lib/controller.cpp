#include "ros/ros.h"
#include "scanner/controller.h"
#include "scanner/subscriber.h"
#include "scanner/publisher.h"

#define BILLION  			1000000000.0

#define FREE_MOTION_SPEED		0.3
#define CONTACT_MOTION_SPEED		0.3
#define ENTRENCHED_MOTION_SPEED		0.3

#define	d_k				0.5

#define RADIUS_1			0.15
#define RADIUS_2			0.3
#define RADIUS_3			0.4

#define DESTINATION_DISTANCE		1.0

static int sign(float num) {
	if(num > 0)
		return 1;
	if(num < 0)
		return -1;
	return 0;
}

static double scalar_product(double v1[3], double v2[3]) {
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

static double * vector_div(double v1[3], double v2) {
	static double sum[3];
	sum[0] = v1[0] / v2;
	sum[1] = v1[1] / v2;
	sum[2] = v1[2] / v2;

	return sum;
}

static double * vector_div(double v1[3], double v2[3]) {
	static double sum[3];
	sum[0] = v1[0] / v2[0];
	sum[1] = v1[1] / v2[1];
	sum[2] = v1[2] / v2[2];

	return sum;
}

static double * vector_mul(double v1[3], double v2) {
	static double sum[3];
	sum[0] = v1[0] * v2;
	sum[1] = v1[1] * v2;
	sum[2] = v1[2] * v2;

	return sum;
}

static double * vector_mul(double v1[3], double v2[3]) {
	static double sum[3];
	sum[0] = v1[0] * v2[0];
	sum[1] = v1[1] * v2[1];
	sum[2] = v1[2] * v2[2];

	return sum;
}

static double * vector_sum(double v1[3], double v2[3]) {
	static double sum[3];
	sum[0] = v1[0] + v2[0];
	sum[1] = v1[1] + v2[1];
	sum[2] = v1[2] + v2[2];

	return sum;
}

static double * vector_diff(double v1[3], double v2[3]) {
	static double sum[3];
	sum[0] = v1[0] - v2[0];
	sum[1] = v1[1] - v2[1];
	sum[2] = v1[2] - v2[2];

	return sum;
}

static double modulus(double v[3]) {
	return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

static double * check_proxy_contact(double destination[3]) {
	static double * s_k;
	
	int num_points_r1 = 0;
	int num_points_r2 = 0;
	int num_points_r3 = 0;

	double * tmp;

	double p_k[3] = {current_destination.tb_x, current_destination.tb_y, 0.0};
	double n_k[3] = {0.0, 0.0, 0.0};
	double * u_k;
	double * u_kp;

	double p_k_m;
	double n_k_m;
	double u_k_m;
	double u_kp_m;

	for(int i = 0; i < 360; i++) {
		//compute distances of all points in the voxel
		double x_i[3] = {environment.cloud_x[i], environment.cloud_y[i], 0.0};
		double * distance = vector_diff(p_k, x_i);
		double distance_m = modulus(distance);
		
		//check radiuses
		if(distance_m < RADIUS_3) {
			num_points_r3++;	
			tmp = vector_sum(n_k, vector_div(distance, distance_m));
			n_k[0] = tmp[0];
			n_k[1] = tmp[1];
			n_k[2] = tmp[2];
			
			if(distance_m < RADIUS_2) {
				num_points_r2++;
				
				if(distance_m < RADIUS_1)
					num_points_r1++;
			}		
		}
	}

	n_k_m = modulus(n_k);

	if(num_points_r3 > 0) {
		tmp = vector_div(n_k,  n_k_m);
		n_k[0] = tmp[0];
		n_k[1] = tmp[1];
		n_k[2] = tmp[2];
	}
	
	//free motion
	u_k =  vector_diff(destination, p_k);
	u_k_m = modulus(u_k);
	
	//compute proxy plane
	u_kp = vector_diff(u_k, vector_mul(n_k, scalar_product(u_k, n_k)));
	u_kp_m = modulus(u_kp);
	
	// free motion
	if(u_k_m > d_k)
		s_k = vector_mul(u_k, d_k/u_k_m); 
	else 
		s_k = vector_mul(u_k, 1);
	
	current_destination.motion_state = 1;
	current_destination.tb_linear_velocity = FREE_MOTION_SPEED;

	// entrched
	if(num_points_r1 > 0) {
		s_k = vector_mul(n_k, d_k / n_k_m);
		current_destination.motion_state = 3;
		current_destination.tb_linear_velocity = ENTRENCHED_MOTION_SPEED;
	}
	else if(num_points_r2 > 0) {
		current_destination.motion_state = 2;
		current_destination.tb_linear_velocity = CONTACT_MOTION_SPEED;
		if(scalar_product(u_k, n_k) < 0){	
			if(modulus(u_kp) > d_k)
				s_k = vector_mul(u_kp, d_k / u_kp_m);
			else
				s_k = vector_mul(u_kp, 1);
		}	
	}
	
	return s_k;
}

void run_controller_tb_destination() {
	double destination[3] = {current_destination.final_destination_x, current_destination.final_destination_y, 0.0};
	double * s_k = check_proxy_contact(destination);
	current_destination.tb_angular_velocity = NO_VALUE;
	current_destination.destination_x = current_destination.tb_x + s_k[0];
	current_destination.destination_y = current_destination.tb_y + s_k[1];
}

void run_controller_teleop() {
	if(current_destination.motion_state != 2 && current_destination.motion_state != 3) {
		current_destination.final_destination_x = current_destination.tb_x + DESTINATION_DISTANCE * sign(tb_speed.linear.x) * cos(current_destination.tb_yaw);
		current_destination.final_destination_y = current_destination.tb_y + DESTINATION_DISTANCE * sign(tb_speed.linear.x) * sin(current_destination.tb_yaw);
	}
	double destination[3] = {current_destination.final_destination_x, current_destination.final_destination_y, 0.0};

	double * s_k = check_proxy_contact(destination);
	current_destination.tb_linear_velocity = tb_speed.linear.x;
	current_destination.tb_angular_velocity = tb_speed.angular.z;
	current_destination.destination_x = current_destination.tb_x + s_k[0];
	current_destination.destination_y = current_destination.tb_y + s_k[1];
}
