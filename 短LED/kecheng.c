/**

  Name:  Intelligent fan
  time:  2016/12/25
author:  Li_TGVp

**/
#include <reg52.h>                               //���뵥Ƭ�������ļ�
#include <DSB18B20.c>                            //�������ڴ���DSB182B20�¶ȴ�����ģ���c���Գ���
sbit  relay0 = P2^0;                             //����̵���1�Ĵ�������Ϊ��Ƭ����P2^0
sbit  relay1 = P2^1;                             //����̵���2�Ĵ�������Ϊ��Ƭ����P2^1
sbit  relay2 = P2^2;                             //����̵���3�Ĵ�������Ϊ��Ƭ����P2^2
sbit  LED1   = P1;                               //�������ڸ�1���������ʾ��ֵ������ΪP1
sbit  LED2   = P0;                               //�������ڸ�2���������ʾ��ֵ������ΪP0
sbit  PIR    = P2^3;                             //�������ڻ�ȡ�������Ƶ紫������������ΪP2^3
//sbit  aircondition = P2^4;                     //�������ڻ�ȡ�������Ƶ紫������������ΪP2^3
int printftemperature(int temperature);          //���庯��printftemperature()������ʾ��ǰ�¶�
int gettemperature();                            //���庯��gettemperature() ������ȡ��ǰ�¶�
int temper;                                      //�������ͱ���(int)temper����Ϊ�¶ȵĴ���ص�
int main()                                       // C����������
{   
    int temper = gettemperature();               // ���ú���gettemperature()��ȡ��ǰ�¶Ȳ�����temper
    if (PIR == 1)                                //  ͨ���������Ƶ紫�����жϷ����Ƿ����ˣ��о������������
    {
        if (  temper > 35 && temper < 40)            //����¶ȷ���35-40����¶ȶΣ������ø���
        {
            relay0 = 0;
        }
        else if (  temper < 30 && temper > 35)       //����¶ȷ���30-35����¶ȶΣ�����������
        {
            relay1 = 0;
        }
        else if (  temper > 26 && temper < 30)       //����¶ȷ���26-30����¶ȶΣ������õ���
        {
            relay2 = 0;
        }
        /*
        else if (  temper >40 )
        {
        aircondition = 1;
        }
        */
        else                                         //����¶Ȳ��������������¶ȶΣ��򲻶���
        {
            relay0 = 1;
            relay1 = 1;
            relay2 = 1;

        }
        
    }
    else
    {
        relay0 = 1;
        relay1 = 1;
        relay2 = 1;
    }
    printftemperature(temper);                  //���ú���  ��7�����������ʾ�¶�
    return 0;

}
int printftemperature(int temperature)          //��������  printftemperature

{
 unsigned char code LedChar[]={                     // �����������������ʾ0-9���������ʾ��16����
    0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,
    0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E
    };
unsigned char LedBuff[2]={
    0xFF, 0xFF
    };
    P1 = LedChar[temperature / 10];             // ����P1��ʾ�¶ȵ�ʮλ
    P0 = LedChar[temperature %10];              // ����P2��ʾ�¶ȵĸ�λ
    return 0;
}
int gettemperature()                          // ʹ���¶ȴ�����ģ���ȡ��ǰ�¶�
{
    bit res;
    int temp;       
    int intT;  
    Start18B20();      
    
   
           
    res = Get18B20Temp(&temp);  
    if (res)                    
    {
        intT = temp >> 4; 
    }            
    else                        
    {
        return 88;
    }
    Start18B20();              
    return intT;
}
