#include <reg52.h>
//#define uchar unsigned char;
sbit RS = P2^2;	//λ���壬Һ��������/����ѡ��
sbit RW = P2^1;	//λ���壬Һ���Ķ�дѡ��
sbit EN = P2^0;	//λ���壬Һ��ʹ���ź�

//#define LCDPORT P2	  //Һ�������ݿ�

unsigned char code table[]="I LOVE MCU!";	  //��CODE������һ��������ʾ�ĳ����ַ���
unsigned char code table1[]="www.zstudy.com";	  //��CODE������һ��������ʾ�ĳ����ַ���
void delay(unsigned int ms);	//��ʱ����
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
�������ƣ�main
�������ܣ�����������
��ڲ�������
����ֵ����
��ע����
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