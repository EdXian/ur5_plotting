#include "ur_robot.h"


ur_robot::ur_robot(){

}
ur_robot::~ur_robot(){

}

bool ur_robot::setup(char *robot_ip , int robot_port){
    printf("ip = %s , port = %d\n",robot_ip ,robot_port);
    sockfd = socket(AF_INET , SOCK_STREAM , 0);
    if (sockfd == -1){
        printf("Fail to create a socket.");
        return false;
    }
    struct sockaddr_in info;
    bzero(&info,sizeof(info));
    info.sin_family = PF_INET;

    //localhost test
    info.sin_addr.s_addr = inet_addr(robot_ip);
    info.sin_port = htons(robot_port);
    int err = connect(sockfd,(struct sockaddr *)&info,sizeof(info));
    if(err==-1){
        printf("Connection error");
        return false;
    }
}

bool ur_robot::disconnect(char *robot_ip , int port){
    close(sockfd);

}

void ur_robot::set_joint_position(const joint data){
    char buf[300];
    sprintf(buf,"movej([%.3f, %.3f, %.3f, %.3f, %.3f, %.3f], a=%.3f, v=%.3f)\n"
            ,data.base
            ,data.shoulder
            ,data.elbow
            ,data.wrist1
            ,data.wrist2
            ,data.wrist3
            ,acc
            ,vel
            );
    printf("send = \n");
    printf("%s\n",buf);
    int check;
    check = send(sockfd, buf, 200, 0);
    if(check = -1){
        std::cout<<"send error"<<std::endl;
    }
}


void ur_robot::set_tcp_offset(const pose data){

offset.x = data.x;
offset.y = data.y;
offset.z = data.z;

}

void ur_robot::set_tcp_pose(const pose data){
    char buf[400];
        sprintf(buf,"movej(p[%f, %f, %f, %f, %f, %f], a=%f, v=%f)\n"
                ,data.x
                ,data.y
                ,data.z
                ,data.roll
                ,data.pitch
                ,data.yaw
                ,1.0
                ,0.1
                );
    printf("send = \n");
    printf("%s",buf);
    printf("ok\n");
    int check;
    int count =0;
    while(*(buf+count)){
       count++;
    }
    check = send(sockfd, buf, count, 0);
    if(check == -1){
       std::cout<<"send error"<<std::endl;
    }

};

void ur_robot::set_tcp_line(const pose data){
    char buf[300];
        sprintf(buf,"movel(p[%.3f, %.3f, %.3f, %.3f, %.3f, %.3f], a=%.3f, v=%.3f, r=0.02)\n"
                ,data.x
                ,data.y
                ,data.z
                ,data.roll
                ,data.pitch
                ,data.yaw
                ,1.0
                ,0.1
                );
    printf("send = \n");
    printf("%s",buf);
    printf("ok\n");
    int check;
    int count =0;
    while(*(buf+count)){
       count++;
    }
    check = send(sockfd, buf, count, 0);
    if(check == -1){
       std::cout<<"send error"<<std::endl;
    }
};

bool ur_robot::send_ur_command(std::string data){
    int check;
    int count =0;
    // std::cout << data<<std::endl;
    check = send(sockfd, data.c_str(),data.length(), 0);
    if(check == -1){
       std::cout<<"send error"<<std::endl;
       return false;
    }
}

bool ur_robot::get_tcp_pose(pose &data){

    if(receive_stream_data()){

        data.x = readbytestoDouble(receivemessage , ur::tcp_pose_message::x);
        data.y = readbytestoDouble(receivemessage , ur::tcp_pose_message::y);
        data.z = readbytestoDouble(receivemessage , ur::tcp_pose_message::z);
        data.roll = readbytestoDouble(receivemessage , ur::tcp_pose_message::roll);
        data.pitch = readbytestoDouble(receivemessage , ur::tcp_pose_message::pitch);
        data.yaw = readbytestoDouble(receivemessage , ur::tcp_pose_message::yaw);


        tcp_pose.x = data.x;
        tcp_pose.y = data.y;
        tcp_pose.z = data.z;
        tcp_pose.roll = data.roll;
        tcp_pose.pitch = data.pitch;
        tcp_pose.yaw = data.yaw;

        return  true;
    }
}

bool ur_robot::get_tcp_velocity(pose & data){

    if(receive_stream_data()){

        data.x = readbytestoDouble(receivemessage , ur::tcp_vel_message::vx);
        data.y = readbytestoDouble(receivemessage , ur::tcp_vel_message::vy);
        data.z = readbytestoDouble(receivemessage , ur::tcp_vel_message::vz);
        data.roll = readbytestoDouble(receivemessage , ur::tcp_vel_message::vroll);
        data.pitch = readbytestoDouble(receivemessage , ur::tcp_vel_message::vpitch);
        data.yaw = readbytestoDouble(receivemessage , ur::tcp_vel_message::vyaw);


        tcp_pose.x = data.x;
        tcp_pose.y = data.y;
        tcp_pose.z = data.z;
        tcp_pose.roll = data.roll;
        tcp_pose.pitch = data.pitch;
        tcp_pose.yaw = data.yaw;

        return  true;
    }
}


bool ur_robot::get_joint_position(joint &data){

    if(receive_stream_data()){

        data.base = readbytestoDouble(receivemessage , ur::joint_position_message::base);
        data.shoulder = readbytestoDouble(receivemessage , ur::joint_position_message::shoulder);
        data.elbow = readbytestoDouble(receivemessage , ur::joint_position_message::elbow);
        data.wrist1 = readbytestoDouble(receivemessage , ur::joint_position_message::wrist1);
        data.wrist2 = readbytestoDouble(receivemessage , ur::joint_position_message::wrist2);
        data.wrist3 = readbytestoDouble(receivemessage , ur::joint_position_message::wrist3);

        return  true;
    }
}


bool ur_robot::get_tcp_force(pose &data){

    if(receive_stream_data()){

        data.x = readbytestoDouble(receivemessage , ur::tcp_force_message::fx);
        data.y = readbytestoDouble(receivemessage , ur::tcp_force_message::fy);
        data.z = readbytestoDouble(receivemessage , ur::tcp_force_message::fz);
        data.roll = readbytestoDouble(receivemessage , ur::tcp_force_message::troll);
        data.pitch = readbytestoDouble(receivemessage , ur::tcp_force_message::tpitch);
        data.yaw = readbytestoDouble(receivemessage , ur::tcp_force_message::tyaw);


        return  true;
    }
}

int32_t ur_robot::get_message_length(){
receive_stream_data();
  int32_t data=0 ;

 data |=  receivemessage[0] <<24;
 data |=   receivemessage[1] <<16;
 data |=   receivemessage[2] <<8;
 data |=   receivemessage[3] <<0;


return data;
}

double ur_robot::readbytestoDouble(uint8_t* Message ,int offset){


    double value;
    uint64_t tmp[8];
    int64_t data = 0 ;
    for(int i=0;i<8;i++){
        tmp[i] = Message[offset+i];
    }

    data |= tmp[0]<<56;
    data |= tmp[1]<<48;
    data |= tmp[2]<<40;
    data |= tmp[3]<<32;
    data |= tmp[4]<<24;
    data |= tmp[5]<<16;
    data |= tmp[6]<<8;
    data |= tmp[7]<<0;
/*
    for(int64_t i=0;i<8;i++){
        data |= tmp[0]<<(56 - i*8);
    }
*/
    value = int2Double(data);

    return value;

}


int64_t ur_robot::readbytestoInt(uint8_t* Message ,int offset){


    uint64_t tmp[8];
    int64_t data = 0 ;
    for(int i=0;i<8;i++){
        tmp[i] = Message[offset+i];
    }

    data |= tmp[0]<<56;
    data |= tmp[1]<<48;
    data |= tmp[2]<<40;
    data |= tmp[3]<<32;
    data |= tmp[4]<<24;
    data |= tmp[5]<<16;
    data |= tmp[6]<<8;
    data |= tmp[7]<<0;
/*
    for(int64_t i=0;i<8;i++){
        data |= tmp[0]<<(56 - i*8);
    }
*/
    return data;

}

double ur_robot::int2Double(const uint64_t data){
    bool negative = data & 0x8000000000000000;
    int64_t exponet = data & 0x7ff0000000000000;
    exponet = exponet >> 52;
    int64_t exponet_bias = 1023;
    double sign = 1;
    int64_t fraction = data & 0xfffffffffffff;
    double dfraction;
    if(negative){
        sign=-1;
    }else{
        sign=1;
    }

   // std::cout<< "exponet"<<exponet - exponet_bias <<std::endl;
    //dfraction = (double)(  1  +    fraction * pow(2,-52)   );

    //std::cout << "fra" <<(double)(log<<52) <<std::endl;
    unsigned long log = 1;
    dfraction = (double)( 1 +  (fraction/(double)(log<<52)));

    //std::cout<< dfraction<<std::endl;
    int64_t d_exponent = exponet - exponet_bias;

    if( d_exponent < 0 ){

       // double value = sign * pow(2,exponet - exponet_bias)*dfraction;
        d_exponent*=-1;

         return  sign/ (((double)(1L<<d_exponent)))*dfraction ;
    }else{
        //double value = sign*dfraction * pow(2,exponet - exponet_bias);
         //double value = sign*dfraction * (((double)(1L<<d_exponent)));
         return sign*dfraction * (((double)(1L<<d_exponent)));
    }
}
double ur_robot::get_robot_mode(){

    if(receive_stream_data()){

        double data   = readbytestoDouble(receivemessage ,756); // 756
        data = readbytestoDouble(receivemessage ,772);
        data = readbytestoDouble(receivemessage ,780);
        data = readbytestoDouble(receivemessage ,788);
        data = readbytestoDouble(receivemessage ,796);
        data = readbytestoDouble(receivemessage ,804);

    }
}

bool ur_robot::receive_stream_data(void){
    int state;
    state = recv(sockfd,receivemessage,sizeof(receivemessage),0);
    if(state == -1){
        return false;
    }else{
        return true;
    }
}
