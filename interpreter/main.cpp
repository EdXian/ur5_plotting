#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <vector>
#include <ur_robot.h>
#include <string.h>
using namespace std;
 vector<string> cmd_vector;
 vector<string> gcode_cmd_vector;
ur_robot::pose readtext(std::string text);
std::string decode(const ur_robot::pose data);
//movej(p[0.800, -0.100, 0.100, 2.2400, -2.2424, 0.000], a=1.000, v=0.100, r=0)\n
double offset_x = 0.600;
double offset_y = -0.100;
double offset_z = -0.170;
ur_robot::pose last_pose;
int count = 0;

int main()
{
    FILE * gcode_file;
    long lSize;
    char * buffer;
    size_t result;

    FILE * ur_file;
    ur_file = fopen ("urfile.txt","w");


  gcode_file = fopen ("dynamics.ngc","rb");
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


    last_pose.x = offset_x;
    last_pose.y = offset_y;
    last_pose.z = offset_z;

    istringstream f(buffer);
    string s;
    while (getline(f, s, '\n')) {

        cmd_vector.push_back(s);

    }
    std::cout<< "================================="<<std::endl;

    //only the prefix of text with "G" is a valid command.
    for(int it = 0 ; it <cmd_vector.size() ; it++){

    if(cmd_vector[it].compare(0,1,"G") != 0){

         continue;
         }
        gcode_cmd_vector.push_back(cmd_vector[it]);
    }

    for(int it=0; it< gcode_cmd_vector.size();it++){
        std::string data = gcode_cmd_vector[it];

        std::cout << decode(readtext(data));
        if (ur_file!=NULL)
          {
            fputs (decode(readtext(data)).c_str(),ur_file);

          }

    }

    //std::cout << "count :" <<     count <<std::endl;
    if (result != lSize) {fputs ("Reading error",stderr); exit (3);}
    fclose (gcode_file);
    fclose(ur_file);
    free (buffer);
    return 0;
}

ur_robot::pose readtext(std::string text){

    istringstream f(text);
    string s;
    std::vector<string> data;

    ur_robot::pose pose;


    pose.x = 0;
    pose.y = 0;
    pose.z = 0;
    //movej(p[0.800, -0.100, 0.100, 2.2400, -2.2424, 0.000], a=1.000, v=0.100, r=0)\n
    pose.roll = 2.24;
    pose.pitch = -2.24;
    pose.yaw = 0.000;
    while (getline(f, s, ' ')) {
        data.push_back(s);
    }

    for(int i=0 ; i<data.size() ; i++){
        if(data[i].at(0)=='G'){
         continue;
        }else if(data[i].at(0)=='X'){
            pose.x = atof(data[i].substr(1,data[i].length()-1).c_str())/1000 +offset_x;
        }else if(data[i].at(0)=='Y'){
            pose.y = atof(data[i].substr(1,data[i].length()-1).c_str())/1000 + offset_y;
        }else if(data[i].at(0)=='Z'){
            pose.z = atof(data[i].substr(1,data[i].length()-1).c_str())/600 +offset_z;
        }
    }
    if((pose.x == 0)&& (pose.y == 0)){

        pose.x = last_pose.x ;
        pose.y = last_pose.y ;

        //std::cout<< "x " <<pose.x << " y " << pose.y << " z " <<pose.z <<std::endl;
    }
    if(pose.z==0){
        pose.z = last_pose.z;
        //std::cout<< "x " <<pose.x << " y " << pose.y << " z " <<pose.z <<std::endl;

    }


    count++;

    last_pose.x = pose.x;
    last_pose.y = pose.y;
    last_pose.z = pose.z;

    //decode(pose);

    return pose;
}



std::string decode(const ur_robot::pose data){
    char buf[300];
    int buf_count =0;
    std::string textdata;
  //  std::string data();

//    sprintf(buf,"movel(p[%.5f, %.5f, %.5f, %.5f, %.5f, %.5f], a=%.3f, v=%.3f, r=0.03)\n"
//            ,data.x
//            ,data.y
//            ,data.z
//            ,data.roll
//            ,data.pitch
//            ,data.yaw
//            ,0.1
//            ,0.7
//            );
        sprintf(buf,"movep(p[%.5f, %.5f, %.5f, %.5f, %.5f, %.5f], a=%.3f, v=%.3f, r=%.5f)\n"
                ,data.x
                ,data.y
                ,data.z
                ,data.roll
                ,data.pitch
                ,data.yaw
                ,1.2
                ,0.1
                ,0.0000
                );
    while(*(buf+buf_count)){
       buf_count++;
    }
    textdata.assign(buf, 0 , buf_count );
    //textdata.append("\n");
    return textdata;
};







