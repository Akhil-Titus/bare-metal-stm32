#include <mpu6050.h>
#include "stm32f1xx.h"
#include "i2c.h"
#include <stdint.h>
#include <stdio.h>



int main(void)
{

    i2c1_init();
    mpu6050_test_connection();
}
