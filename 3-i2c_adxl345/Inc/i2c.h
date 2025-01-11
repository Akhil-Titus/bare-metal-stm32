/*
 * i2c.h
 *
 *  Created on: Jan 11, 2025
 *      Author: Akhil
 */


#ifndef I2C_H
#define I2C_H

//#define STM32F103x6
#include "stm32f1xx.h"

void i2c_module_test_function_led(void);

void i2c1_init(void);

void i2c1_byte_read(char sAddr, char mAddr, char *data);

void i2c1_burst_read(char sAddr, char mAddr, int n, char* data);

void i2c1_burst_write(char sAddr, char mAddr, int n, char* data);

#endif
