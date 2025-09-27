#include "stdio.h"

int main()
{
 int a = 1;
 int b = 3;
 
 int c = 0;
 
 c = a + b;
 
 if(c == 3)
 {
 	asm volatile ("li x30,0x1");
 }
 else if(c == 4)
 {
 	asm volatile ("li x30,0x2");
 }
 else 
 {
 	asm volatile ("li x30,0x0");
}

return 0;
}
