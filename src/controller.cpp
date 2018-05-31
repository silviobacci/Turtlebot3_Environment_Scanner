#include "controller.h"
#include "teleop_handler.h"
#include "lidar_handler.h"

void run_controller() {
	if(distance < 0.18)
		tb_speed.linear.x = -0.01;

	if(distance == 0.0)
		tb_speed.linear.x = 0;
}
