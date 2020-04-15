#include"reg52.h"       					 //头文件  定义单片机的特殊功能
unsigned int ms=0; 
unsigned int	sec=17;
unsigned int	min=20;
unsigned int	hour=18;

unsigned char code tab[]={0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90,0xff,0xbf};
unsigned char dspbuf[]={10,10,10,10,10,10,10,10};	
char dspcom=0;
void display();                           //函数的声明


void main()
{
	TMOD=0x01;                       //T0模式1    16位
	TH0=(65536-2000)/256;            //  2ms 装载计数初值寄存器
	TL0=(65536-2000)/256;
	ET0=1;                 				  //使能定时器中断
	EA=1;               						//使能全局中断
	TR0=1;													//启动定时器
	
	while(1)
	{
		if(sec==60)
		{
				sec=0;
				min++;
		}
		if(min==60)
		{
				min=0;
				hour++;
		}
		if(hour==24)
		{
					hour=0;
		}
		dspbuf[0]=10;
		dspbuf[1]=10;
		dspbuf[2]=10;
		dspbuf[3]=1;
		dspbuf[4]=0;
		dspbuf[5]=2;                
		dspbuf[6]=3;
		dspbuf[7]=6;    

	}
}

                                       //T0的中断服务程序
void t0_isr()    interrupt 1                 //T0中断  中断号1
{
	                                    //模式1不能自动重载初值  需要手动重载   程序实验
		TH0=(65536-2000)/256;                   //2ms  装载计数初值寄存在定时器
		TL0=(65536-2000)%256;
	  ms++;

	if(ms==500)                          //2ms*500次等于1s
	{
		 ms=0;                         //下次还是从0开始
	 	sec++;                          //1s  到了   秒++
	}
	display();                                 //函数的调用
}
                                    //函数定义  函数实现了什么的功能
void display()                              // 显示函数
//clear
{
P0=0xff;
P2=P2&0x1f|0xe0;
P2=P2&0x1f;

//select
P0=1<<dspcom;
P2=P2&0x1f|0xc0;
P2=P2&0x1f;

//data
P0=tab[dspbuf[dspcom]];
P2=P2&0x1f|0xe0;
P2=P2&0x1f;

if(++dspcom==8)
	dspcom=0;
 
}
