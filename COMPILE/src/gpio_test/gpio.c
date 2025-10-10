#include "gpio.h"
#include "timer.h"   // 如果没有这个头，删掉本行即可

// 预防性：若库里没有实现 set_pin_function，提供一个弱符号空实现以避免链接错误。
// 若将来你添加了真正的实现，链接器会优先用真正的实现覆盖这个弱实现。
__attribute__((weak)) void set_pin_function(int pin, int function) { (void)pin; (void)function; }

// 简单延时（仿真用）
static void delay_cycles(volatile unsigned int cycles) {
  while (cycles--) { __asm__ volatile ("nop"); }
}

int main(void)
{
  // 选择你要观测的 GPIO 引脚；这里用 0..3 号做演示
  const int pins[] = {0, 1, 2, 3, 4, 5, 6, 7};
  const int num_pins = sizeof(pins) / sizeof(pins[0]);

  // 1) 配置为输出
  for (int i = 0; i < num_pins; ++i) {
    set_gpio_pin_direction(pins[i], DIR_OUT);
    set_gpio_pin_value(pins[i], 0);   // 先拉低
  }

  // 2) 简单跑马灯：依次点亮、全亮/全灭、再交替翻转，便于在波形里观察
  while (1) {
    // 依次点亮
    for (int i = 0; i < num_pins; ++i) {
      set_gpio_pin_value(pins[i], 1);
      delay_cycles(5000);
      set_gpio_pin_value(pins[i], 0);
      delay_cycles(2000);
    }

    // 全亮
    for (int i = 0; i < num_pins; ++i) set_gpio_pin_value(pins[i], 1);
    delay_cycles(20000);

    // 全灭
    for (int i = 0; i < num_pins; ++i) set_gpio_pin_value(pins[i], 0);
    delay_cycles(20000);

    // 交替翻转一段时间
    for (int t = 0; t < 8; ++t) {
      for (int i = 0; i < num_pins; ++i) {
        int v = get_gpio_pin_value(pins[i]);
        set_gpio_pin_value(pins[i], !v);
      }
      delay_cycles(10000);
    }
  }

  // 不会到达这里
  // return 0;
}
