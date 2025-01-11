#include "stm32f1xx.h"
#include "i2c.h"
#include "adxl345.h"
#include <stdint.h>
#include <stdio.h>

int16_t x, y, z;
float xg, yg, zg;

extern uint8_t data_rec[6];
const float FOUR_G_SCALE_FACT = 0.0078;

int main(void)
{

    // adxl345_module_test_function_led();

    adxl_init();

    while (1)
    {
        adxl_read_values(DATA_START_ADDR);

        x = ((data_rec[1] << 8) | data_rec[0]);
        y = ((data_rec[3] << 8) | data_rec[2]);
        z = ((data_rec[5] << 8) | data_rec[4]);

        xg = x * FOUR_G_SCALE_FACT;
        yg = y * FOUR_G_SCALE_FACT;
        zg = z * FOUR_G_SCALE_FACT;
    }
}
