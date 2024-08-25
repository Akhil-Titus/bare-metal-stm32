#include "stm32f1xx.h"
#include "i2c.h"
#include "adxl345.h"

int main(void)
{
    i2c1_init();
    adxl345_module_test_function_led();
}