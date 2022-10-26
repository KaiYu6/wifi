#include <atomic>      //原子类型数据，确保了在同一时刻只有唯一的线程对这个资源进行访问。

#include "rc_indoor/udp_client.h"
#include "rc_indoor/keyboard.h"

class RC
{
public:
    float steer = 0;   //-1～1，float类型默认6位小数
    float throttle = 0;    //-1～1
    int key;    //键盘输入
    int flag = 1;   // 中断标志位
    UDP udp;

    std::atomic_bool control_run_flag_atomic_{};
    std::atomic_bool monitor_run_flag_atomic_{};

    RC();   //构造函数
    void ControlLoopRun();  //控制线程
    void MonitorLoopRun();  //监视进程
    void ShutDownThread();  //关闭线程
};