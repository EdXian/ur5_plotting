#ifndef _UR_ROBOT_H
#define _UR_ROBOT_H
#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include <ur_definition.h>
#define buf_length 1060
class ur_robot{

public:
typedef struct p{
    double x;
    double y;
    double z;
    double roll;
    double yaw;
    double pitch;
}pose;

typedef struct q{
   double base;
   double shoulder;
   double elbow;
   double wrist1;
   double wrist2;
   double wrist3;
}joint;


    ur_robot();
    ~ur_robot();
    bool setup(char *robot_ip , int port);

    bool disconnect(char *robot_ip , int port);
    void sethome();

    void init();

    void set_tcp_offset(const pose data);
    void set_tcp_pose(const pose data);
    void set_joint_position(const joint data);
    void set_velocity(double vel);
    void set_acceleration(double acc);
    void set_blending_radius(double r);

    void set_tcp_line(const pose data);


    bool get_tcp_pose(pose& data);

    double get_robot_mode();




    //bool get_tcp_force(pose &data);

    bool get_tcp_velocity(pose & data);
    bool get_tcp_line(pose& data);
    bool get_joint_position(joint& data);
    int32_t get_message_length();
    bool get_joint_velocity(joint& data);
    bool get_tcp_force(pose& data);

    void get_tcp_transform();
    joint joint_position;
    joint joint_vel;
    pose tcp_pose;
    pose tcp_vel;
    pose offset ;
    double acc;
    double vel;
    double interval;
    double blend_radius;
    uint8_t receivemessage[1060];
    //socket
    int sockfd ;
    bool connection_flag;
    bool receive_stream_data(void);
    double readbytestoDouble(uint8_t* Message ,int offset);
    int64_t readbytestoInt(uint8_t* Message ,int offset);

    double int2Double(const uint64_t data);
    bool send_ur_command(std::string data);
   // void readtext(std::string data);

};




#endif
