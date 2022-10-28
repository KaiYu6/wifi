#include <stdio.h>          //标准输入输出
#include <iostream>         //流式输入输出
#include <string.h>         //各种操作字符数组的函数
#include <errno.h>          //通过错误码来回报错误资讯
#include <stdlib.h>         //各种通用工具函数
#include <unistd.h>         //针对系统调用的封装
#include <sys/types.h>      //基本系统数据类型
#include <sys/socket.h>     //socket套接字是通信的基石，是支持TCP/IP协议的路通信的基本操作单元
#include <netinet/in.h>     //互联网地址族
#include <arpa/inet.h>      //网络操作

#define DEST_PORT 8002                      //服务器端口
#define DSET_IP_ADDRESS  "10.106.20.149"     //服务器IP

class UDP
{  
public:
    int sock_fd;    //套接字
    struct sockaddr_in addr_serv;   //网络地址结构
    int len;    //内存尺寸
    int len_msg = 25;     //消息长度
    int send_num;   //标志位
    int recv_num;   //标志位
    char send_buf[100]={0}; //存储要发的数据
    char recv_buf[100]; //存储接收的数据

    UDP();  //构造函数
    void udp_init();    //初始化
    void udp_client(float steer, float throttle, int flag);   //UDP通信
    void udp_close();   //关闭套接字
};
