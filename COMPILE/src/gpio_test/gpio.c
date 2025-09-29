#include "gpio.h"
#include "string_lib.h"

int main() {
    // 设置 GPIO0~GPIO7 为输出
    for (int i = 0; i < 8; i++) {
        set_gpio_pin_direction(i, DIR_OUT);
    }

    // 测试：依次输出高低电平
    while (1) {
        // 全部置高
        for (int i = 0; i < 8; i++) {
            set_gpio_pin_value(i, 1);
        }
        printf("GPIO0~7 set HIGH\n");

        // 可以在这里添加延时函数，如果有实现的话
        // delay_ms(500);

        // 全部置低
        for (int i = 0; i < 8; i++) {
            set_gpio_pin_value(i, 0);
        }
        printf("GPIO0~7 set LOW\n");

        // 延时
        // delay_ms(500);
    }

    return 0;
}
