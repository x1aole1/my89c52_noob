#include <reg52.h>
//#define uchar unsigned char;
sbit RS = P2^2;	//位定义，液晶的数据/命令选择
sbit RW = P2^1;	//位定义，液晶的读写选择
sbit EN = P2^0;	//位定义，液晶使能信号

//#define LCDPORT P2	  //液晶的数据口

unsigned char code table[]="I LOVE MCU!";	  //在CODE区定义一个用于显示的常量字符串
unsigned char code table1[]="www.zstudy.com";	  //在CODE区定义一个用于显示的常量字符串
void delay(unsigned int ms);	//延时函数
unsigned char num;
void write_com(unsigned char com)
{
	RS=0;
	P2=com;
	delay(20);
	EN=1;
	delay(20);
	EN=0;
}
void write_data(unsigned char date)
{
	RS=1;
	P2=date;
	delay(20);
	EN=1;
	delay(20);
	EN=0;
}
void init()
{
	RW=0;
	EN=0;
	write_com(0x38);
	write_com(0x0f);
	write_com(0x06);
	write_com(0x01);
}
/******************************************************************************
函数名称：main
函数功能：程序主函数
入口参数：无
返回值：无
备注：无
*******************************************************************************/
void main(void)
{
	init();
	write_com(0x80);
	for(num=0;num<11;num++)
	{
		write_data(table[num]);
		delay(20);
	}
		write_com(0x80+0x40);
	for(num=0;num<14;num++)
	{
		write_data(table1[num]);
		delay(20);
	}
	while(1);
}


void delay(unsigned int ms)
{
	unsigned char j = 110;
	for(;ms > 0;ms--) while(--j);	
}