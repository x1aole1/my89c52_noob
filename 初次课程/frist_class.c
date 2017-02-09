#include <reg52.h>

sbit LED1 = P1^0;
sbit LED2 = P1^1;
sbit LED3 = P1^4;
int main()
	{
	LED1 = 0;
	LED2 = 1;
	LED3 = 0;
	return 0;
	}