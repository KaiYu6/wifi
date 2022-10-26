#include <ros/ros.h>   //ros
#include "rc_indoor/indoor_rc.h"

using namespace std;

RC::RC()
{
    steer = 0;
    throttle = 0;
    key = 0;
    flag = 1;
    control_run_flag_atomic_.store(true);
    monitor_run_flag_atomic_.store(true);
}

void RC::ControlLoopRun()
{
    while (control_run_flag_atomic_.load())
    {
        // 此处添加控制算法，得到 steer 和 throttle
        steer = 0.5;
        throttle = 0.5;
        udp.udp_client(steer, throttle, flag);
    }
}
void RC::MonitorLoopRun()
{
    while (monitor_run_flag_atomic_.load())
    {
        key = scanKeyboard();
        if(key == 32)   //空格，回车10，Esc27
        {
            flag = 0;
            ROS_INFO_STREAM("Keyboard Interrupt!");
        }
        else 
        {
            flag = 1;
            ROS_INFO_STREAM("Keyboard:" << key);
        }
    }
}

void RC::ShutDownThread()      //关闭线程
{
    control_run_flag_atomic_.store(false);
    monitor_run_flag_atomic_.store(false);
    udp.udp_close();
}
