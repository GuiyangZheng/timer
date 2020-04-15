#include"reg52.h"       					 //ͷ�ļ�  ���嵥Ƭ�������⹦��
unsigned int ms=0; 
unsigned int	sec=17;
unsigned int	min=20;
unsigned int	hour=18;

unsigned char code tab[]={0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90,0xff,0xbf};
unsigned char dspbuf[]={10,10,10,10,10,10,10,10};	
char dspcom=0;
void display();                           //����������


void main()
{
	TMOD=0x01;                       //T0ģʽ1    16λ
	TH0=(65536-2000)/256;            //  2ms װ�ؼ�����ֵ�Ĵ���
	TL0=(65536-2000)/256;
	ET0=1;                 				  //ʹ�ܶ�ʱ���ж�
	EA=1;               						//ʹ��ȫ���ж�
	TR0=1;													//������ʱ��
	
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

                                       //T0���жϷ������
void t0_isr()    interrupt 1                 //T0�ж�  �жϺ�1
{
	                                    //ģʽ1�����Զ����س�ֵ  ��Ҫ�ֶ�����   ����ʵ��
		TH0=(65536-2000)/256;                   //2ms  װ�ؼ�����ֵ�Ĵ��ڶ�ʱ��
		TL0=(65536-2000)%256;
	  ms++;

	if(ms==500)                          //2ms*500�ε���1s
	{
		 ms=0;                         //�´λ��Ǵ�0��ʼ
	 	sec++;                          //1s  ����   ��++
	}
	display();                                 //�����ĵ���
}
                                    //��������  ����ʵ����ʲô�Ĺ���
void display()                              // ��ʾ����
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
