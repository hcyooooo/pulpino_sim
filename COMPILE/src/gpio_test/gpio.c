#include "gpio.h"
#include "string_lib.h"
#include "utils.h"

void delay(volatile int cycles) {
    for (volatile int i = 0; i < cycles; i++);
}

int main() {
    // 设置 GPIO0~GPIO7 为输出
    for (int i = 0; i < 8; i++) {
        set_gpio_pin_direction(i, DIR_OUT);
    }

    printf("GPIO0~GPIO7 configured as output\n");

    while (1) {
        // 全部置高
        for (int i = 0; i < 8; i++) {
            set_gpio_pin_value(i, 1);
        }
        printf("GPIO0~7 set HIGH\n");
        delay(1000000);

        // 全部置低
        for (int i = 0; i < 8; i++) {
            set_gpio_pin_value(i, 0);
        }
        printf("GPIO0~7 set LOW\n");
        delay(1000000);

        // 单个引脚轮流置高
        for (int i = 0; i < 8; i++) {
            // 先清零所有
            for (int j = 0; j < 8; j++)
                set_gpio_pin_value(j, 0);
            set_gpio_pin_value(i, 1);
            printf("GPIO%d set HIGH\n", i);
            delay(500000);
        }
    }

    return 0;
}
