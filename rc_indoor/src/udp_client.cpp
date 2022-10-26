// 功能：用于UDP通信
// 作者：余凯
// 参考：https://blog.csdn.net/weixin_42100710/article/details/122135577
// 日期：2022-3-22

#include "rc_indoor/udp_client.h"

using namespace std;

UDP::UDP()
{
    /* udp socket */
    //家族名：AF_INET，因特网，ipv4；无连接的套接字：SOCK_DGRAM，创建UDP套接字；指定需要使用的协议，0不用显式指定
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0); //创建套接字
    if(sock_fd < 0)         //-1表示错误
    {
        perror("socket");   //把一个描述性错误消息输出到标准错误 stderr
        exit(1);
    }

    memset(&addr_serv, 0, sizeof(addr_serv));               //将addr_serv数组全体内存空间按字节整体清零
    addr_serv.sin_family = AF_INET;                         //地址族
    addr_serv.sin_addr.s_addr = inet_addr(DSET_IP_ADDRESS); //服务器ip，不是本机ip
    addr_serv.sin_port = htons(DEST_PORT);                  //服务器端口
    len = sizeof(addr_serv);        //就是求数组addr_serv占用的所有内存尺寸，不会理会其中装载什么数据。
}

void UDP::udp_client(float steer, float throttle, int flag)
{
    if(flag)
    {
        // cout << "Please enter the data to transfer!" << endl;
        // scanf("%s", &send_buf); // 直接输出终端输入内容
        string s = to_string(steer + 1) + "," + to_string(throttle + 1) + "\r\n";    //字符串长17
        strcpy(send_buf,s.c_str());
    }
    else
    {
        string s = "1.000000,1.000000\r\n";
        strcpy(send_buf,s.c_str());
        cout << "Keyboard Interrupt!" << endl;
    }
    cout << "send_buf:" << send_buf << endl;
    
    // for(int i=0;i<51;i++)
    // {
    //   mycheck ^= send_buf[i]; //对要发送的数据亦或校验，接收端再次校验，保证接收端的数据正确
    // }
    // send_buf[51]= mycheck; //存储校验数
    // send_buf[52]=0xEE;
    // send_buf[53]=0xDD;

    //ssize_t sendo(ints,const void *msg,size_t len,int flags,const struct sockaddr *to,socklen_ttolen);
    /*
    2>函数功能：
    向目标主机发送消息
    3>函数形参：
    Ø  s:套接字描述符。
    Ø  *msg:发送缓冲区
    Ø  len:待发送数据的长度
    Ø  flags:控制选项，一般设置为0或取下面的值
    (1)MSG_OOB:在指定的套接字上发送带外数据(out-of-band data),该类型的套接字必须支持带外数据（eg:SOCK_STREAM）.
    (2)MSG_DONTROUTE:通过最直接的路径发送数据，而忽略下层协议的路由设置。
    Ø  to:用于指定目的地址
    Ø  tolen:目的地址的长度。
    4>函数返回值：
    执行成功后返回实际发送数据的字节数，出错返回-1，错误代码存入errno中。
    */
    send_num = sendto(sock_fd, send_buf, len_msg, 0, (struct sockaddr *)&addr_serv, len);

    if(send_num < 0) //判断发送是否成功
    {
        perror("sendto error:");
        exit(1);
    }
    else
    {
        // cout << "SEND OK" << endl;
    }
    /*
    1>函数原型：
    #include<sys/types.h>
    #include<sys/socket.h>
    ssize_t recvfrom(int s,void *buf,size_t len,intflags,struct sockaddr *from,socklen_t *fromlen);
    2>函数功能：接收数据
    3>函数形参：
    Ø  int s:套接字描述符
    Ø  buf:指向接收缓冲区，接收到的数据将放在这个指针所指向的内存空间。
    Ø  len:指定了缓冲区的大小。
    Ø  flags:控制选项,一般设置为0或取以下值
    (1)MSG_OOB:请求接收带外数据
    (2)MSG_PEEK:只查看数据而不读出
    (3)MSG_WAITALL:只在接收缓冲区时才返回。
    Ø  *from:保存了接收数据报的源地址。
    Ø  *fromlen:参数fromlen在调用recvfrom前为参数from的长度，调用recvfrom后将保存from的实际大小。
    4>函数返回值：
    执行成功后返回实际接收到数据的字节数，出错时则返回-1，错误代码存入errno中。
    */
    // recv_num = recvfrom(sock_fd, recv_buf, sizeof(recv_buf), 0, (struct sockaddr *)&addr_serv, (socklen_t *)&len);

    // if(recv_num < 0) //判断数据是否接收成功
    // {
    //     perror("recvfrom error:");
    //     exit(1);
    // }
    // else
    // {
    //     ROS_INFO("RECV OK");
    // }

    // recv_buf[recv_num] = '\0';
    // printf("client receive %d bytes: %s\n", recv_num, recv_buf);//打印接收到的数据 
}

void UDP::udp_close()
{
    close(sock_fd);
}
