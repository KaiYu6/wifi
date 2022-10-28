// 功能：主函数，室内蚊车
// 作者：余凯
// 参考：
// 日期：2022-4-20

#include <ros/ros.h>   //ros
#include <pthread.h>   //多线程
#include <thread>      //线程
#include <chrono>            //与时间有关

#include "rc_indoor/indoor_rc.h"

using namespace std;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "rc_indoor");
    ros::NodeHandle n;
    RC rc;

    std::thread loop_execute1(&RC::ControlLoopRun,&rc);  // 开启子线程1
    std::thread loop_execute2(&RC::MonitorLoopRun,&rc);  // 开启子线程2
    
    ros::Rate loop_rate(1);    //while以50Hz循环

    while(ros::ok()) 
    {
        ros::spinOnce(); 
        loop_rate.sleep(); 
    }

    rc.ShutDownThread();  // spin 结束即在终端 ctrl-c 主线程，此时需要关闭子线程
    loop_execute1.join();
    loop_execute2.join();

    return 0;
}

