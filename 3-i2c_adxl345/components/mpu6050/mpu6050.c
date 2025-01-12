/*
 * adxl345.c
 *
 *  Created on: Jan 11, 2025
 *      Author: Akhil
 */

#include "mpu6050.h"

#include <stdio.h>
#include "i2c.h"

char data;
uint8_t data_rec[6];

/** Get Device ID.
 * Module for testing library
 * @return void
 */
void mpu6050_module_test_function_led(void);

/** Verify the I2C connection.
 * Make sure the device is connected and responds as expected.
 * @return True if connection is valid, FALSE otherwise
 */
bool mpu6050_test_connection();

/** Read multiple bits from an 8-bit device register.
 * @param slaveAddr I2C slave device address
 * @param regAddr Register regAddr to read from
 * @param bitStart First bit position to read (0-7)
 * @param length Number of bits to read (not more than 8)
 * @param data Container for right-aligned value (i.e. '101' read from any bitStart position will equal 0x05)
 * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in readTimeout)
 */
void mpu6050_read_bits(uint8_t slaveAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t *data);

/** Get Device ID.
 * This register is used to verify the identity of the device (0b110100).
 * @return Device ID (should be 0x68, 104 dec, 150 oct)
 * @see MPU6050_RA_WHO_AM_I
 * @see MPU6050_WHO_AM_I_BIT
 * @see MPU6050_WHO_AM_I_LENGTH
 */
uint8_t mpu6050_get_device_id();


void mpu6050_module_test_function_led(void)
{
    i2c_module_test_function_led();
}

void mpu6050_read_bits(uint8_t slaveAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t *data)
{
    uint8_t tmp;
    // Reading one byte from the register
    i2c1_burst_read(slaveAddr, regAddr, 1, (char *)&tmp); // Ensure `tmp` is passed as a pointer

    uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
    tmp &= mask;                     // Apply mask to isolate the bits
    tmp >>= (bitStart - length + 1); // Shift to align the bits
    *data = tmp;
}

uint8_t mpu6050_get_device_id()
{
    uint8_t tmp;
    mpu6050_read_bits(MPU6050_DEFAULT_ADDRESS, MPU6050_RA_WHO_AM_I, MPU6050_WHO_AM_I_BIT, MPU6050_WHO_AM_I_LENGTH, &tmp);
    return tmp;
}

bool mpu6050_test_connection()
{
    return mpu6050_get_device_id() == 0x34 ? TRUE : FALSE; // 0b110100; 8-bit representation in hex = 0x34
}
