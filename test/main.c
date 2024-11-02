/**
 * Solution to fix float issue
 * */


#include "stm32f1xx.h"
#include <stdio.h>

int16_t x = 1, y = 2, z = 3;
float xg, yg, zg;

const float FOUR_G_SCALE_FACT = 0.0078;

int main(void)
{
    while (1)
    {
        // Use scaled values directly as floats
        xg = x * FOUR_G_SCALE_FACT;
        yg = y * FOUR_G_SCALE_FACT;
        zg = z * FOUR_G_SCALE_FACT;
    }
}
