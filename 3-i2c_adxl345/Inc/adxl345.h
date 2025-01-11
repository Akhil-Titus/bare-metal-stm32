/*
 * adxl345.h
 *
 *  Created on: Jan 11, 2025
 *      Author: Akhil
 */

#ifndef ADXL345_H_
#define ADXL345_H_

#ifndef ADXL345_H
#define ADXL345_H

#include "i2c.h"

#define DEVID_R 0X00
#define DEVICE_ADDR 0X53
#define DATA_FORMAT_R 0x31
#define POWER_CTL_R 0x2D
#define DATA_START_ADDR 0x32
#define DATA_FORMAT_R 0x31

#define FOUR_G 0x01
#define RESET 0x00
#define SET_MEASURE_B 0x08



void adxl345_module_test_function_led(void);

void adxl_init(void);   

void adxl_read_values(uint8_t reg);

#endif


#endif /* ADXL345_H_ */
