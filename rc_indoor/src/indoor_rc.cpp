#include <ros/ros.h>   //ros
#include "rc_indoor/indoor_rc.h"

using namespace std;

RC::RC()
{
    steer = 0;
    throttle = 0;
    control_freq = 20;
    key = 0;
    flag = 1;
    control_run_flag_atomic_.store(true);
    monitor_run_flag_atomic_.store(true);
}

void RC::ControlLoopRun()
{
    while (control_run_flag_atomic_.load())
    {
        std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();

        // 此处添加控制算法，得到 steer 和 throttle
        steer = 0.2;
        throttle = 0.2;
        control_freq = 20;
        udp.udp_client(steer, throttle, flag);        
        
        std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast< std::chrono::milliseconds>(t2-t1).count();
        int delta_T = 1000/control_freq - (int)duration;

        if(delta_T<=0) ;
        else
            std::this_thread::sleep_for(std::chrono::milliseconds(delta_T)); 
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
