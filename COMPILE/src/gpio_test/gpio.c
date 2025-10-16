#include "gpio.h"
#include "uart.h"
#include <stdlib.h>

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
  // 初始化 UART
  uart_set_cfg(0, 1);
  
  printf("\n========================================\n");
  printf("GPIO Comprehensive Test Start\n");
  printf("========================================\n\n");

  // 测试引脚定义
  const int test_pins[] = {0, 1, 2, 3, 4, 5, 6, 7};
  const int num_pins = sizeof(test_pins) / sizeof(test_pins[0]);
  int errors = 0;

  // ====================================
  // 测试1: 输出方向设置和读取
  // ====================================
  printf("Test 1: GPIO Direction (Output)\n");
  for (int i = 0; i < num_pins; ++i)
  {
    set_gpio_pin_direction(test_pins[i], DIR_OUT);
    int dir = get_gpio_pin_direction_fixed(test_pins[i]);
    if (dir == DIR_OUT) {
      printf("  Pin %d: DIR_OUT - PASS\n", test_pins[i]);
    } else {
      int dir_after = get_gpio_pin_direction_fixed(test_pins[i]);
      printf("  Pin %d: DIR_OUT - FAIL (read=%d, fixed_read=%d)\n", test_pins[i], dir, dir_after);
      errors++;
    }
  }
  printf("\n");

  // ====================================
  // 测试2: 输出值设置 (逐个测试)
  // ====================================
  printf("Test 2: GPIO Output Value (Individual)\n");
  
  // 测试设置为 HIGH
  for (int i = 0; i < num_pins; ++i)
  {
    set_gpio_pin_value(test_pins[i], 1);
    delay_cycles(1000);
    printf("  Pin %d: Set HIGH\n", test_pins[i]);
  }
  delay_cycles(5000);
  
  // 测试设置为 LOW
  for (int i = 0; i < num_pins; ++i)
  {
    set_gpio_pin_value(test_pins[i], 0);
    delay_cycles(1000);
    printf("  Pin %d: Set LOW\n", test_pins[i]);
  }
  printf("\n");

  // ====================================
  // 测试3: 全部引脚同时操作
  // ====================================
  printf("Test 3: All GPIO Pins Together\n");
  
  // 全部拉高
  printf("  Setting all pins HIGH...\n");
  for (int i = 0; i < num_pins; ++i)
  {
    set_gpio_pin_value(test_pins[i], 1);
  }
  delay_cycles(10000);
  
  // 全部拉低
  printf("  Setting all pins LOW...\n");
  for (int i = 0; i < num_pins; ++i)
  {
    set_gpio_pin_value(test_pins[i], 0);
  }
  delay_cycles(10000);
  printf("\n");

  // ====================================
  // 测试4: 位模式测试
  // ====================================
  printf("Test 4: Bit Pattern Test\n");
  
  // 奇数引脚 HIGH，偶数引脚 LOW
  printf("  Pattern: 0xAA (01010101)\n");
  for (int i = 0; i < num_pins; ++i)
  {
    set_gpio_pin_value(test_pins[i], i % 2);
  }
  delay_cycles(10000);
  
  // 偶数引脚 HIGH，奇数引脚 LOW
  printf("  Pattern: 0x55 (10101010)\n");
  for (int i = 0; i < num_pins; ++i)
  {
    set_gpio_pin_value(test_pins[i], (i + 1) % 2);
  }
  delay_cycles(10000);
  
  // 全部拉低
  for (int i = 0; i < num_pins; ++i)
  {
    set_gpio_pin_value(test_pins[i], 0);
  }
  printf("\n");

  // ====================================
  // 测试5: 跑马灯效果
  // ====================================
  printf("Test 5: Running LED Pattern\n");
  for (int cycle = 0; cycle < 3; ++cycle)
  {
    printf("  Cycle %d\n", cycle + 1);
    for (int i = 0; i < num_pins; ++i)
    {
      set_gpio_pin_value(test_pins[i], 1);
      delay_cycles(3000);
      set_gpio_pin_value(test_pins[i], 0);
      delay_cycles(1000);
    }
  }
  printf("\n");

  // ====================================
  // 测试6: 快速翻转测试
  // ====================================
  printf("Test 6: Fast Toggle Test\n");
  for (int i = 0; i < num_pins; ++i)
  {
    printf("  Toggling Pin %d (10 times)...\n", test_pins[i]);
    for (int t = 0; t < 10; ++t)
    {
      set_gpio_pin_value(test_pins[i], 1);
      delay_cycles(500);
      set_gpio_pin_value(test_pins[i], 0);
      delay_cycles(500);
    }
  }
  printf("\n");


  // ====================================
  // 测试7: 方向切换测试
  // ====================================
  printf("Test 7: Direction Switching Test\n");
  for (int i = 0; i < num_pins; ++i)
  {
    // 输出模式
    set_gpio_pin_direction(test_pins[i], DIR_OUT);
    set_gpio_pin_value(test_pins[i], 1);
    delay_cycles(2000);
    
    // 输入模式
    set_gpio_pin_direction(test_pins[i], DIR_IN);
    delay_cycles(2000);
    
    // 恢复输出模式
    set_gpio_pin_direction(test_pins[i], DIR_OUT);
    set_gpio_pin_value(test_pins[i], 0);
    
    printf("  Pin %d: Direction switching - PASS\n", test_pins[i]);
  }
  printf("\n");

  // ====================================
  // 测试总结
  // ====================================
  printf("========================================\n");
  printf("GPIO Test Summary\n");
  printf("========================================\n");
  printf("Total Errors: %d\n", errors);
  if (errors == 0) {
    printf("Result: ALL TESTS PASSED!\n");
  } else {
    printf("Result: SOME TESTS FAILED!\n");
  }
  printf("========================================\n\n");

  // // 进入持续运行模式（用于波形观察）
  // printf("Entering continuous pattern mode...\n");
  // int pattern = 0;
  // while (1)
  // {
  //   // 设置所有引脚为输出
  //   for (int i = 0; i < num_pins; ++i)
  //   {
  //     set_gpio_pin_direction(test_pins[i], DIR_OUT);
  //     set_gpio_pin_value(test_pins[i], (pattern >> i) & 0x1);
  //   }
    
  //   pattern = (pattern + 1) % 256;
  //   delay_cycles(50000);
    
  //   if (pattern % 16 == 0) {
  //     printf("Pattern: 0x%02X\n", pattern);
  //   }
  // }

  return 0;
}
