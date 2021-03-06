#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <vector>
#include <ur_robot.h>
#include <string.h>
#include <chrono>
#include <thread>
using namespace std;
int robot_port;
char *robot_ip ;
ur_robot robot;
ur_robot::pose data;
int count = 0;

ur_robot::pose current_pose;
uint8_t mode;
ur_robot::pose force;
ur_robot::joint joint;
int counter = 0;
void connection(void){

    while(1){
        robot.get_tcp_velocity(force);
        std::cout << "======"<<counter++<<"====="<<std::endl;
//       std::cout << joint.base *57.3 <<std::endl
//                  << joint.shoulder*57.3 <<std::endl
//                  << joint.elbow *57.3<<std::endl
//                  << joint.wrist1 *57.3<<std::endl
//            ~      << joint.wrist2 *57.3<<std::endl
//                  << joint.wrist3 *57.3<<std::endl;
       std::cout << force.x <<std::endl
                  << force.y <<std::endl
                  << force.z<<std::endl;
       //std::cout << robot.get_message_length() <<std::endl;
        std::this_thread::sleep_for (std::chrono::milliseconds(1000/125));
    }

}

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
    // end: for each input argument

    // Done!
    return;
}


int main(int argc , char *argv[])
{
    parse_commandline(argc , argv ,robot_ip , robot_port );
    robot.setup(robot_ip,robot_port);

    std::thread first (connection);
    std::vector<string> cmd_vector;
    FILE * gcode_file;
    long lSize;
    char * buffer;
    size_t result;



  gcode_file = fopen ("urfile.txt","rb");

  if (gcode_file==NULL) {fputs ("File error",stderr); exit (1);}
    else{
      printf("the file exist.");
  }
    fseek (gcode_file , 0 , SEEK_END);
    lSize = ftell (gcode_file);
    rewind (gcode_file);
    buffer = (char*) malloc (sizeof(char)*lSize);
    if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}
    result = fread (buffer,1,lSize,gcode_file);
    printf("================================");
    printf("size  =  %ld\n",lSize);
    printf("get:\n");


    istringstream f(buffer);
    string s;
    while (getline(f, s, '\n')) {

        cmd_vector.push_back(s);

    }


    std::string data1("movej(p[0.600, -0.100, -0.100, 2.2400, -2.2424, 0.000], a=1.000, v=0.100, r=0)\n");
    //robot.send_ur_command(data1);
    sleep(20);

    sleep(2);

    while(1){


//            std::string datax("force_mode(p[0.600, -0.100, -0.100, 2.2400, -2.2424, 0.000], [0, 0, 1, 0, 0, 0], [0.0, 0.0, -20.0, 0.0, 0.0, 0.0], 2, [0.01, 0.01, 0.150, 0.01, 0.01, 0.01])\n");
//            robot.send_ur_command(datax);
//            usleep(10000);
   //     std::string data("force_mode(p[0.600, -0.100, -0.120, 2.2400, -2.2424, 0.000], [0, 0, 1, 0, 0, 0], [0.0, 0.0, -20.0, 0.0, 0.0, 0.0], 2, [0.1, 0.1, 0.150, 0.01, 0.01, 0.01])\n");
 //       robot.send_ur_command(data);
//        usleep(10000);
        std::string data5("movec(p[0.600, -0.150, 0.0, 2.2400, -2.2424, 0.000], p[0.595, -0.10134, 0.100, 2.2400, -2.2424, 0.000], a=0.6, v=0.04, r=0.004)\n");
      // robot.send_ur_command(data5);
        sleep(2);

//        robot.send_ur_command(datax);
//        robot.send_ur_command(data_sync);
//        usleep(100000);
        std::string datay("movel(p[0.600, -0.100, -0.0, 2.2400, -2.2424, 0.000], a=0.600, v=0.030, r=0.001)\n");
        //robot.send_ur_command(datay);
        sleep(2);

//        robot.send_r_command(datax);
//        robot.send_ur_command(data_sync);
//        usleep(100000);
        std::string dataz("movel(p[0.600, -0.150, -0.0, 2.2400, -2.2424, 0.000], a=0.600, v=0.030, r=0.001)\n");
        //robot.send_ur_command(dataz);
        sleep(2);

      std::string data2("movel(p[0.700, -0.100, 0.100, 2.2400, -2.2424, 0.000], a=1.000, v=0.100, t=1.2, r=0.07)\n");
         //robot.send_ur_command(data2);
//        robot.get_tcp_pose(current_pose);
//        usleep(700000);

//        std::cout<< "x " <<current_pose.x
//                    << " y " <<current_pose.y
//                    << " z " <<current_pose.z<<std::endl;

//        std::string data3("movel(p[0.700, -0.200, 0.100, 2.2400, -2.2424, 0.000], a=1.000, v=0.100, t=1.2, r=0.07)\n");
//        robot.send_ur_command(data3);
//        robot.get_tcp_pose(current_pose);
//        usleep(700000);
//        std::cout<< "x " <<current_pose.x
//                    << " y " <<current_pose.y
//                    << " z " <<current_pose.z<<std::endl;


//        std::string data4("movel(p[0.600, -0.200, 0.100, 2.2400, -2.2424, 0.000], a=1.000, v=0.100, t=1.2, r=0.07)\n");
//        robot.send_ur_command(data4);
//        robot.get_tcp_pose(current_pose);
//        usleep(700000);
//        std::cout<< "x " <<current_pose.x
//                    << " y " <<current_pose.y
//                    << " z " <<current_pose.z<<std::endl;




//        std::string data5("movel(p[0.600, -0.100, 0.100, 2.2400, -2.2424, 0.000], a=1.000, v=0.100, t=1.2, r=0.07)\n");
//        robot.send_ur_command(data5);
//        robot.get_tcp_pose(current_pose);
//        usleep(700000);
//        std::cout<< "x " <<current_pose.x
//                    << " y " <<current_pose.y
//                    << " z " <<current_pose.z<<std::endl;

}

    robot.disconnect("192.168.50.50",30003);
    return 0;

}
