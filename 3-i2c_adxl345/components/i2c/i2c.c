/*
 * i2c.c
 *
 *  Created on: Jan 11, 2025
 *      Author: Akhil Titus
 */


#include "i2c.h"


// i2c1 is connected to apb1 
// but peripherals can only be activated afted apb2 enable (selecting mode like alternate function)
void i2c_init(char i2c, unsigned short speed_mode)
{
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN; // enable alternate function

    if (i2c == 1)
    {
        RCC->APB1ENR |= RCC_APB1ENR_I2C1EN; // enable i2c1

        /*enable gpio o/p AF open-drain*/
        // PB6 mode 01, config mode 11
        GPIOB->CRL |= GPIO_CRL_MODE6_0;
        GPIOB->CRL &= ~GPIO_CRL_MODE6_1;
        GPIOB->CRL |= GPIO_CRL_CNF6_0 | GPIO_CRL_CNF6_1; // Open drain alternate  config mode 11

        // PB7 mode 01, config mode 11
        GPIOB->CRL |= GPIO_CRL_MODE7_0;
        GPIOB->CRL &= ~GPIO_CRL_MODE7_1;
        GPIOB->CRL |= GPIO_CRL_CNF7_0 | GPIO_CRL_CNF7_1; // Open drain alternate config mode 11

        I2C1->CR1 |= I2C_CR1_SWRST; /*enter reset mode*/
        I2C1->CR1 &= ~I2C_CR1_SWRST; /*come out of reset mode*/
        
        // I2C1->CR2 = I2C_CR2_FREQ_3; /*Set peripheral clock freq*/
        I2C1->CR2 = 0x8;
        I2C1->CCR = speed_mode;
        I2C1->TRISE = 0x9; // since that is the selected clock freq (mentioned in data sheet)
        I2C1->CR1 |= I2C_CR1_PE;  /*Peripheral enable*/
    }
    else if (i2c == 2)
    {
        RCC->APB1ENR |= RCC_APB1ENR_I2C2EN; // enable i2c1

        /*enable gpio o/p AF open-drain*/
        // PB6 mode 01, config mode 11
        GPIOB->CRH |= GPIO_CRH_MODE10_0;
        GPIOB->CRH &= ~GPIO_CRH_MODE10_1;
        GPIOB->CRH |= GPIO_CRH_CNF10_0 | GPIO_CRH_CNF10_1; // Open drain alternate  config mode 11

        // PB7 mode 01, config mode 11
        GPIOB->CRH |= GPIO_CRH_MODE11_0;
        GPIOB->CRH &= ~GPIO_CRH_MODE11_1;
        GPIOB->CRH |= GPIO_CRH_CNF11_0 | GPIO_CRH_CNF11_1; // Open drain alternate config mode 11

        I2C2->CR1 |= I2C_CR1_SWRST; /*enter reset mode*/
        I2C2->CR1 &= ~I2C_CR1_SWRST; /*come out of reset mode*/
        
        // I2C1->CR2 = I2C_CR2_FREQ_3; /*Set peripheral clock freq*/
        I2C2->CR2 = 0x8;
        I2C2->CCR = speed_mode;
        I2C2->TRISE = 0x9; // since that is the selected clock freq (mentioned in data sheet)
        I2C2->CR1 |= I2C_CR1_PE;  /*Peripheral enable*/
    }
}

void i2c_start(char i2c)
{
    if (i2c == 1)
    {
        I2C1->CR1 |= I2C_CR1_START;
        while (!(I2C1->SR1 & 1))
        {
        }; // wait
    }
    else if (i2c == 2)
    {
        I2C2->CR1 |= I2C_CR1_START;
        while (!(I2C2->SR1 & 1))
        {
        }; // wait
    }
}

// sending address + R/W
void i2c_address(char i2c, char address, char RW)
{
    volatile int tmp;
    if (i2c == 1)
    {
        I2C1->DR = (address | RW);

        while (!(I2C1->SR1 & I2C_SR1_ADDR))
        {
        }; /* wait until addr flag is set*/

        while ((I2C1->SR1 & I2C_SR1_ADDR))
        {
            tmp = I2C1->SR1;
            tmp = I2C1->SR2;
            if ((I2C1->SR1 & I2C_SR1_ADDR))
            {
                break;
            }
        }
    }
    else if (i2c == 2)
    {
        I2C1->DR = (address | RW);

        while (!(I2C2->SR1 & I2C_SR1_ADDR))
        {
        }; /* wait until addr flag is set*/

        while ((I2C2->SR1 & I2C_SR1_ADDR))
        {
            tmp = I2C2->SR1;
            tmp = I2C2->SR2;
            if ((I2C2->SR1 & I2C_SR1_ADDR))
            {
                break;
            }
        }
    }
}

void i2c_data_transfer(char i2c, char data)
{
    if (i2c == 1)
    {
        while (!(I2C1->SR1 & I2C_SR1_TXE))
        {
        };
        I2C1->DR = data;
        while (!(I2C1->SR1 & I2C_SR1_TXE))
        {
        };
    }
    else if (i2c == 2)
    {
        while (!(I2C2->SR1 & I2C_SR1_TXE))
        {
        };
        I2C2->DR = data;
        while (!(I2C2->SR1 & I2C_SR1_TXE))
        {
        };
    }
}

void i2c_stop(char i2c)
{
    volatile int tmp;
    if (i2c == 1)
    {
        tmp = I2C1->SR1;
        tmp = I2C1->SR2; // just in case
        I2C1->CR1 |= I2C_CR1_STOP;
    }
    else if (i2c == 2)
    {
        tmp = I2C2->SR1;
        tmp = I2C2->SR2; // just in case
        I2C2->CR1 |= I2C_CR1_STOP;
    }
}

void i2c_write(char i2c, char address, char data[])
{
    int i = 0;
    i2c_start(i2c);
    i2c_address(i2c, address, 0);
    while (data[i])
    {
        i2c_data_transfer(i2c, data[i]);
        i++;
    }
    i2c_stop(i2c);
}

























// #define I2C_100KHZ              80          // check again
// // #define SD_MODE_MAX_RISE_TIME   17          // check agin
// // #define CR1_PE                  (1U << 0)   


void i2c_module_test_function_led(void)
{
    const uint32_t PIN_13 = GPIO_ODR_ODR13; // Alias for pin 13

    // Your code here
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

    GPIOC->CRH |= GPIO_CRH_MODE13_0 | GPIO_CRH_MODE13_1;
    GPIOC->CRH &= ~(GPIO_CRH_CNF13_0 | GPIO_CRH_CNF13_1);

    while (1)
    {
        GPIOC->ODR ^= PIN_13;
        for (int i = 0; i < 500000; i++)
            ;
    }
}


// void i2c1_init(void)
// {
//     /* enable clock access to gpio B*/
//     // RCC->APB2ENR |= GPIOBEN;
//     RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

//     /* Set PB6 & PB7 output type to open drain */
//     /* Set PB6 & PB7 mode to alternate functions as i2c GPIOx_CRL*/

//     // 1. first choose mode as output
//     // 2. if mode is output, the cnf reg can be set to make the port alternate function

//     // PB6 mode 01
//     GPIOB->CRL |= GPIO_CRL_MODE6_0;
//     GPIOB->CRL &= ~GPIO_CRL_MODE6_1;

//     GPIOB->CRL |= GPIO_CRL_CNF6_0 | GPIO_CRL_CNF6_1; // Open drain alternate mode 11

//     // PB7 mode 01
//     GPIOB->CRL |= GPIO_CRL_MODE7_0;
//     GPIOB->CRL &= ~GPIO_CRL_MODE7_1;

//     GPIOB->CRL |= GPIO_CRL_CNF7_0 | GPIO_CRL_CNF7_1; // Open drain alternate mode 11

//     /* enable pull up for PB6 & PB7 */

//     /* Enable clock access to i2c1 */
//     // RCC->APB1ENR |= I2C1EN;     // enable i2c1
//     RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

//     /*enter reset mode*/
//     // I2C1->CR1 |= (1U<<15);
//     I2C1->CR1 |= I2C_CR1_SWRST;

//     /*come out of reset mode*/
//     // I2C1->CR1 &= ~(1U<<15);
//     I2C1->CR1 &= ~ I2C_CR1_SWRST;

//     /*Set peripheral clock freq*/
//     // I2C1->CR2 = (1U<<4);        // 16 MHz 2^4 = 16
//     I2C1->CR2 &= ~I2C_CR2_FREQ_4;

//     /*Set I2C to standard mode, 100Khz clock
//     * Frequency = 1/Time period 
//     * 100 = 1/Time period
//     * Time Period=CCR×TPCLK1        (TPCLK1  = 125ns)
//     * time period = 1/ frequency ie 1/100khz = 1000 ns
//     * CCR = 1000ns / 125ns = 80
//     * 
//     * */
//     I2C1->CCR =  I2C_100KHZ;
//     // I2C1->CCR = I2C_CCR_CCR;         ??

//     /*Set rise time*/
//     // I2C1->TRISE |= SD_MODE_MAX_RISE_TIME;
//     I2C1->TRISE = I2C_TRISE_TRISE;

//     /*Peripheral enable*/
//     // I2C1->CR1 |= CR1_PE;
//     I2C1->CR1 |= I2C_CR1_PE;
// }

// void i2c1_byte_read(char sAddr, char mAddr, char *data)
// {
//     volatile int tmp;

//     // wait until bus not busy
//     while (I2C1->SR2 & I2C_SR2_BUSY);

//     // Start condition
//     I2C1->CR1 |= I2C_CR1_START;

//     // wait until start bit is set
//     while (!(I2C1->SR2 & I2C_SR1_SB));

//     /* transmit slave address + write*/
//     I2C1->DR = sAddr << 1;      // here LSB will be 0

//     /* wait until addr flag is set*/
//     while (!(I2C1->SR1 & I2C_SR1_ADDR));

//     /* Clear the address flag by reading the SR2 */
//     tmp = I2C1->SR2;

//     /* Send memory address */
//     I2C1->DR = mAddr;

//     /* Wait until transmitter is empty*/
//     while (!(I2C1->SR1 & I2C_SR1_TXE));

    
//     /***************************************
//     * Generate restart
//     */
//     I2C1->CR1 |= I2C_CR1_START;

//     // wait until start bit is set
//     while (!(I2C1->SR2 & I2C_SR1_SB));

//     /* transmit slave address + read*/
//     I2C1->DR = sAddr << 1 | 1;      // | operation to make LSB to 1

//     /* wait until addr flag is set*/
//     while (!(I2C1->SR1 & I2C_SR1_ADDR));

//     /* Disable the acknowledge*/
//     I2C1->CR1 &= ~I2C_CR1_ACK;

//     /* Clear the address flag by reading the SR2 */
//     tmp = I2C1->SR2;

//     /* Generte a stop after data is received*/
//     I2C1->CR1 |= I2C_CR1_STOP;

//     /* Wait until receiver flag is set*/
//     while (!(I2C1->SR1 & I2C_SR1_RXNE));

//     /* Read from data register*/
//     *data++ = I2C1->DR;
// }

// void i2c1_burst_read(char sAddr, char mAddr, int n, char* data)
// {
//     volatile int tmp;

//     // wait until bus not busy
//     while (I2C1->SR1 & I2C_SR2_BUSY);

//     // Start condition
//     I2C1->CR1 |= I2C_CR1_START;

//     // wait until start bit is set
//     while (!(I2C1->SR1 & I2C_SR1_SB));

//     /* transmit slave address + write*/
//     I2C1->DR = sAddr << 1;   

//     /* wait until addr flag is set*/
//     while (!(I2C1->SR1 & I2C_SR1_ADDR));

//     /* Clear the address flag by reading the SR2 */
//     tmp = I2C1->SR2;

//     /* Send memory address */
//     I2C1->DR = mAddr;

//     /* Wait until transmitter is empty*/
//     while (!(I2C1->SR1 & I2C_SR1_TXE));

    
//     /***************************************
//     * Generate restart
//     */
//     I2C1->CR1 |= I2C_CR1_START;

//     // wait until start bit is set
//     while (!(I2C1->SR2 & I2C_SR1_SB));

//     /* transmit slave address + read*/
//     I2C1->DR = sAddr << 1 | 1;      // | operation to make LSB to 1

//     /* wait until addr flag is set*/
//     while (!(I2C1->SR1 & I2C_SR1_ADDR));

//     /* Clear the address flag by reading the SR2 */
//     tmp = I2C1->SR2;

//     /* Enable the acknowledge*/
//     I2C1->CR1 |= I2C_CR1_ACK;

//     while(n > 0U)
//     {
//         /* if one byte */
//         if(n == 1U)
//         {
//             /* Disable the acknowledge*/
//             I2C1->CR1 &= ~I2C_CR1_ACK;

//             /* Generte stop*/
//             I2C1->CR1 |= I2C_CR1_STOP;

//             /* Wait until receiver flag is set*/
//             while (!(I2C1->SR1 & I2C_SR1_RXNE));

//             /* Read from data register*/
//             *data++ = I2C1->DR;

//             break;
//         }
//         else
//         {
//             /* Wait until receiver flag is set*/
//             while (!(I2C1->SR1 & I2C_SR1_RXNE));

//             /* Read from data register*/
//             *data++ = I2C1->DR;

//             n--;
//         }
//     }
// }

// void i2c1_burst_write(char sAddr, char mAddr, int n, char* data)
// {
//     volatile int tmp;

//      // wait until bus not busy
//     while (I2C1->SR2 & I2C_SR2_BUSY);

//     // Start condition
//     I2C1->CR1 |= I2C_CR1_START;

//     // wait until start bit is set
//     while (!(I2C1->SR2 & I2C_SR1_SB));

//      /* transmit slave address + write*/
//     I2C1->DR = sAddr << 1;   

//     /* wait until addr flag is set*/
//     while (!(I2C1->SR1 & I2C_SR1_ADDR));

//     /* Clear the address flag by reading the SR2 */
//     tmp = I2C1->SR2;

//     /* Wait until transmitter is empty*/
//     while (!(I2C1->SR1 & I2C_SR1_TXE));

//     /* Send memory address */
//     I2C1->DR = mAddr;

//     for (int i = 0; i < n; i++)
//     {
//         /* Wait until transmitter is empty*/
//         while (!(I2C1->SR1 & I2C_SR1_TXE));

//         I2C1->DR = *data++;
//     }

//     /* Wait until transfer id finished*/
//     while (!(I2C1->SR1 & I2C_SR1_BTF));

//     /* Generte stop*/
//     I2C1->CR1 |= I2C_CR1_STOP;
// }
