#include "stm32f1xx.h"
#include <stdint.h>
#include <stdio.h>
#include "i2c.h"
#include "mpu6050.h"



int main(void)
{

    i2c_init(1, I2C_FM);
    // mpu6050_test_connection();
}
