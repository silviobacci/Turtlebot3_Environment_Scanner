#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include <iostream>

#include <geometry_msgs/Twist.h>
#include <sensor_msgs/LaserScan.h>

// UDP define
#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
 

#define BUFLEN 512
#define REMOTE_PORT 12001
#define LOCAL_PORT 12002
#define LOCAL_IP "192.168.1.7"
#define REMOTE_IP "192.168.1.2"


geometry_msgs::Twist twist_msg;
ros::Publisher cmd_vel_publisher;

int main (int argc, char **argv)
{
	ros::init(argc, argv, "dan_udp_publisher");
	ros::NodeHandle node_obj;
	//ros::Publisher number_publisher = node_obj.advertise<std_msgs::Int32>("/numbers",10);
	cmd_vel_publisher = node_obj.advertise<geometry_msgs::Twist>("/cmd_vel",1);
	//ros::Rate loop_rate(50);
	int number_count = 0;

	//UDP SOCKET CODE
	struct sockaddr_in si_me, si_other;
     
    	int s, i, recv_len;
	socklen_t slen = sizeof(si_other); 
    	float rxbuf[BUFLEN];
	float txbuf[BUFLEN];

	ROS_INFO("UDP SOCKET OPENING ... ");
     
    	//create a UDP socket
    	if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    	{
		ROS_INFO("ERROR CREATING UDP SOCKET ");
    	}
	
	// zero out the structure
    	memset((char *) &si_me, 0, sizeof(si_me));
     
    	si_me.sin_family = AF_INET;
    	si_me.sin_port = htons(LOCAL_PORT);
    	si_me.sin_addr.s_addr = htonl(INADDR_ANY);

    	//bind socket to port
    	if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
    	{
		ROS_INFO("ERROR BINDING UDP SOCKET");
    	}


	ROS_INFO("STARTING ROS NODE LOOP");


	while(ros::ok())
	{
		
		//std_msgs::Int32 msg;
		//msg.data = number_count;
		//ROS_INFO("MESSAGE PUBLISHED %d",msg.data);
		//number_publisher.publish(msg);
		//ros::spinOnce();

		//UDP RECEIVE	
		char *pchar;
		pchar = (char *) &rxbuf[0];
		if ((recv_len = recvfrom(s, pchar, BUFLEN*sizeof(float), 0, (struct sockaddr *) &si_other, &slen)) > 0)
        	{

            		ROS_INFO("UDP PACKET RECEIVED %f %f", rxbuf[0], rxbuf[1]);

			twist_msg.linear.x = rxbuf[0];
			twist_msg.angular.z = rxbuf[1];
			cmd_vel_publisher.publish(twist_msg);


			txbuf[0] = rxbuf[0];
			txbuf[1] = -7.7;
			pchar = (char *) &txbuf[0];
			sendto(s, pchar, 2*sizeof(float), 0, (struct sockaddr*) &si_other, slen);		
        	}	

		//loop_rate.sleep();
		ros::spinOnce();

	}

	return 0;

}
