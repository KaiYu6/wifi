// 功能：用于响应键盘
// 作者：余凯
// 参考：https://blog.csdn.net/qqliuzhitong/article/details/120239169
// 日期：2022-4-20

#include "rc_indoor/keyboard.h"
 
int scanKeyboard()
{
	int in;
	struct termios new_settings;
	struct termios stored_settings;
    //设置终端参数
	tcgetattr(0,&stored_settings);
	new_settings = stored_settings;
	new_settings.c_lflag &= (~ICANON);
	new_settings.c_cc[VTIME] = 0;
	tcgetattr(0,&stored_settings);
	new_settings.c_cc[VMIN] = 1;
	tcsetattr(0,TCSANOW,&new_settings);
	in = getchar();
	tcsetattr(0,TCSANOW,&stored_settings);
 
	return in;
}
