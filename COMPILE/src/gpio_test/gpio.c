#include "gpio.h"
#include "timer.h"  // 如果没有这个头，删掉本行即可
#include <stdlib.h> // 引入 malloc 和 free

// 预防性：若库里没有实现 set_pin_function，提供一个弱符号空实现以避免链接错误。
// 若将来你添加了真正的实现，链接器会优先用真正的实现覆盖这个弱实现。
// __attribute__((weak)) void set_pin_function(int pin, int function)
// {
//   (void)pin;
//   (void)function;
// }

// 动态分配的 pin 状态数组
int *pin_state;

// 简单延时（仿真用）
static void delay_cycles(volatile unsigned int cycles)
{
  while (cycles--)
  {
    __asm__ volatile("nop");
  }
}

int main(void)
{
  // 选择你要观测的 GPIO 引脚；这里用 0..7 号做演示
  const int pins[] = {0, 1, 2, 3, 4, 5, 6, 7};
  const int num_pins = sizeof(pins) / sizeof(pins[0]);

  // 动态分配内存，初始化 pin_state 数组
  pin_state = (int *)malloc(num_pins * sizeof(int));
  if (pin_state == NULL)
  {
    // 如果分配失败，退出程序
    return -1;
  }

  // 初始化 pin_state 数组，假设所有引脚初始状态为低电平
  for (int i = 0; i < num_pins; ++i)
  {
    pin_state[i] = 0; // 初始化为低电平
    set_gpio_pin_direction(pins[i], DIR_OUT);
    set_gpio_pin_value(pins[i], 0); // 先拉低
  }

  // 依次点亮、全亮、全灭、交替翻转
  while (1)
  {
    // 1) 依次点亮
    for (int i = 0; i < num_pins; ++i)
    {
      pin_state[i] = 1; // 设置当前引脚为高电平
      set_gpio_pin_value(pins[i], pin_state[i]);
      delay_cycles(5000);
      pin_state[i] = 0; // 设置当前引脚为低电平
      set_gpio_pin_value(pins[i], pin_state[i]);
      delay_cycles(2000);
    }

    // 2) 全亮
    for (int i = 0; i < num_pins; ++i)
    {
      pin_state[i] = 1; // 设置所有引脚为高电平
      set_gpio_pin_value(pins[i], pin_state[i]);
    }
    delay_cycles(20000);

    // 3) 全灭
    for (int i = 0; i < num_pins; ++i)
    {
      pin_state[i] = 0; // 设置所有引脚为低电平
      set_gpio_pin_value(pins[i], pin_state[i]);
    }
    delay_cycles(20000);

    // 4) 交替翻转
    for (int t = 0; t < 8; ++t)
    {
      for (int i = 0; i < num_pins; ++i)
      {
        pin_state[i] = !pin_state[i]; // 翻转当前引脚状态
        set_gpio_pin_value(pins[i], pin_state[i]);
      }
      delay_cycles(10000);
    }
  }

  // 使用完后释放内存
  free(pin_state);
  return 0;
}