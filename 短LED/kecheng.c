/**

  Name:  Intelligent fan
  time:  2016/12/25
author:  Li_TGVp

**/
#include <reg52.h>                               //引入单片机定义文件
#include <DSB18B20.c>                            //引入用于处理DSB182B20温度传感器模块的c语言程序
sbit  relay0 = P2^0;                             //定义继电器1的处理引脚为单片机的P2^0
sbit  relay1 = P2^1;                             //定义继电器2的处理引脚为单片机的P2^1
sbit  relay2 = P2^2;                             //定义继电器3的处理引脚为单片机的P2^2
sbit  LED1   = P1;                               //定义用于给1号数码管显示赋值的引脚为P1
sbit  LED2   = P0;                               //定义用于给2号数码管显示赋值的引脚为P0
sbit  PIR    = P2^3;                             //定义用于获取人体热势电传感器动作引脚为P2^3
//sbit  aircondition = P2^4;                     //定义用于获取人体热势电传感器动作引脚为P2^3
int printftemperature(int temperature);          //定义函数printftemperature()用来显示当前温度
int gettemperature();                            //定义函数gettemperature() 用来获取当前温度
int temper;                                      //定义整型变量(int)temper来作为温度的处理地点
int main()                                       // C语言主函数
{   
    int temper = gettemperature();               // 调用函数gettemperature()获取当前温度并存入temper
    if (PIR == 1)                                //  通过人体热势电传感器判断房间是否有人，有就允许风扇运行
    {
        if (  temper > 35 && temper < 40)            //如果温度符合35-40这个温度段，则启用高速
        {
            relay0 = 0;
        }
        else if (  temper < 30 && temper > 35)       //如果温度符合30-35这个温度段，则启用中速
        {
            relay1 = 0;
        }
        else if (  temper > 26 && temper < 30)       //如果温度符合26-30这个温度段，则启用低速
        {
            relay2 = 0;
        }
        /*
        else if (  temper >40 )
        {
        aircondition = 1;
        }
        */
        else                                         //如果温度不符合上面三个温度段，则不动作
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
    printftemperature(temper);                  //调用函数  在7段数码管上显示温度
    return 0;

}
int printftemperature(int temperature)          //声明函数  printftemperature

{
 unsigned char code LedChar[]={                     // 设置数组存入用于显示0-9的数码管显示的16进制
    0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,
    0x80, 0x90, 0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E
    };
unsigned char LedBuff[2]={
    0xFF, 0xFF
    };
    P1 = LedChar[temperature / 10];             // 定义P1显示温度的十位
    P0 = LedChar[temperature %10];              // 定义P2显示温度的个位
    return 0;
}
int gettemperature()                          // 使用温度传感器模块获取当前温度
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
