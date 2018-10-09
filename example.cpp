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
#include <ur_robot.h>
#include <cmath>
#include <thread>
#include <pthread.h>
int robot_port;
char *robot_ip ;
ur_robot robot;
ur_robot::pose data;


void
parse_commandline(int argc, char **argv, char *&robot_ip, int &port)
{

    const char *commandline_usage = "usage: ./client3 -a robot_ip -p port";
    int i;


    for (i = 1; i < argc; i++) {


        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            printf("%s\n",commandline_usage);
            throw EXIT_FAILURE;
        }

        if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--addr") == 0) {
            if (argc > i + 1) {
                robot_ip = argv[i + 1];

            } else {
                printf("%s\n",commandline_usage);
                throw EXIT_FAILURE;
            }
        }

        // Baud rate
        if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--port") == 0) {
            if (argc > i + 1) {
                port = atoi(argv[i + 1]);

            } else {
                printf("%s\n",commandline_usage);
                throw EXIT_FAILURE;
            }
        }

    }
    return;
}

ur_robot::pose current_pose;
void connection(void){

    while(1){
        robot.get_tcp_pose(current_pose);
    }

}




int main(int argc , char *argv[])
{
    parse_commandline(argc , argv ,robot_ip , robot_port );
    robot.setup(robot_ip,robot_port);


   std::thread robot_connect(connection);

    int count = 0;

    double offset_x = 0.60;
    double offset_y = -0.120;
    double offset_z = -0.300;
//    std::string datax("movej(p[0.800, -0.100, 0.100, 2.2400, -2.2424, 0.000], a=1.000, v=0.100, r=0)\n");
//    robot.send_ur_command(datax);
    sleep(10);
    while(1){

    data.x =  0.790  ;  //in meters
    data.y =   -0.100;
    data.z =   0.1  ;
    data.roll =  2.2400 ;
    data.pitch = -2.2400 ;
    data.yaw =  0.00 ;

    std::string data1("movej(p[0.790, -0.100, 0.100, 2.2400, -2.2424, 0.000], a=1.000, v=0.100, r=0)\n");
    //robot.send_ur_command(data1);
    robot.set_tcp_pose(data);
    sleep(5);
    std::cout<<"================="<<std::endl;
    std::cout<< "x" <<current_pose.x
             << "y" <<current_pose.y
             << "z" <<current_pose.z;

    data.x =  0.80  ;  //in meters
    data.y =   -0.120;
    data.z =   0.100  ;
    data.roll =  2.24 ;
    data.pitch = -2.2424 ;
    data.yaw =  0.00 ;
    std::string data2("movej(p[0.800, -0.120, 0.100, 2.2400, -2.2424, 0.000], a=1.000, v=0.100, r=0)\n");
    //robot.send_ur_command(data2);
    robot.set_tcp_pose(data);
    sleep(5);
    std::cout<<"================="<<std::endl;
    std::cout<< "x" <<current_pose.x
             << "y" <<current_pose.y
             << "z" <<current_pose.z;





}

   robot.disconnect("192.168.50.50",30003);
   //robot_connect.join();
    return 0;
}
