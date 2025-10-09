#include "utils.h"
#include "string_lib.h"
#include "bar.h"
#include "gpio.h"
#include "spi.h"
int main()
{
  set_pin_function(PIN_MSPI_CSN1, FUNC_EXT2);
  if (get_pin_function(PIN_MSPI_CSN1) == FUNC_EXT2) {
     printf("Successfully enabled func 2 on PIN_MSPI_CSN1\n");
  } else {
     printf("ERROR on enabling func 2 on PIN_MSPI_CSN1\n");
  }

  set_pin_function(PIN_MSPI_CSN2, FUNC_GPIO);
  set_gpio_pin_direction(PIN_MSPI_CSN2, DIR_OUT);
  if (get_gpio_pin_direction(PIN_MSPI_CSN2) == DIR_OUT) {
     printf("Successfully set out dir on PIN_MSPI_CSN2\n");
  } else {
     printf("ERROR on setting out dir on PIN_MSPI_CSN2\n");
  }

  printf("Done!!!\n");

  return 0;
}