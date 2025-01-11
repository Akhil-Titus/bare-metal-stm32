/*
 * adxl345.c
 *
 *  Created on: Jan 11, 2025
 *      Author: Akhil
 */


#include "adxl345.h"
#include "i2c.h"
#include <stdio.h>

char data;
uint8_t data_rec[6];

void adxl345_module_test_function_led(void)
{
    i2c_module_test_function_led();
}

void adxl_read_address(uint8_t reg)
{
    i2c1_byte_read(DEVICE_ADDR, reg, &data);
}

void adxl_write(uint8_t reg, char value)
{
    char data[1];
    data[0] = value;

    i2c1_burst_write(DEVICE_ADDR, reg, 1, data);
}

void adxl_read_values(uint8_t reg)
{
    i2c1_burst_read(DEVICE_ADDR, reg, 6, (char *)data_rec);
}


void adxl_init(void)
{
    i2c1_init();

    /*Read device id */
    adxl_read_address(DEVID_R);

    /*set data format range to +4G*/
    adxl_write(DATA_FORMAT_R, FOUR_G);

    /*Reset all bits*/
    adxl_write(POWER_CTL_R, RESET);

    /* configure power control measure bit*/
    adxl_write(POWER_CTL_R, SET_MEASURE_B);

}