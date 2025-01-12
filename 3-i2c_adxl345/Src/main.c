#include "stm32f1xx.h"
#include <stdint.h>
#include <stdio.h>
#include "i2c.h"
#include "mpu6050.h"



int main(void)
{

    i2c1_init();
    mpu6050_test_connection();
}
