#ifndef _ur_definition__
#define _ur_definition__




namespace ur{

enum port{
    port1=30001,
    port2,
    port3,
    port4
};

enum tcp_pose_message{
    x = 444,
    y = 452,
    z = 460,
    roll = 468,
    pitch = 476,
    yaw = 484
};

enum tcp_vel_message{
    vx = 492,
    vy = 500,
    vz = 508,
    vroll = 516,
    vyaw = 524,
    vpitch = 532
};

enum joint_position_message{
    base=252,
    shoulder=260,
    elbow=268,
    wrist1=276,
    wrist2=284,
    wrist3=292
};

enum joint_velocity_message{
    vbase=300,
    vshoulder,
    velbow,
    vwrist1,
    vwrist2,
    vwrist3
};

enum tcp_force_message{
    fx = 540,
    fy = 548,
    fz = 556,
    troll = 564,
    tpitch = 572,
    tyaw = 580
};

enum robot_mode_message{
    mode1 = 756,
    mode2 = 764,
    mode3 = 812
};
enum joint_mode_message{

};

enum safety_mode_message{

};

enum ur_mode_message{
};


}


#endif
