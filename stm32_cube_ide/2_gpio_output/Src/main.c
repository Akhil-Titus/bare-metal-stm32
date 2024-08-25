#define STM32F103x6
#include "stm32f1xx.h"

#define IOPCEN (1U << 4) // enable gpio C
#define ODR13 (1U << 13) // output data register
#define PIN_13 ODR13

int main(void)
{
    // Your code here
    RCC->APB2ENR |= IOPCEN;
    GPIOC->CRH &= ~(15U << 20);
    GPIOC->CRH |= (1U << 21);

    while (1)
    {
        GPIOC->ODR ^= PIN_13;
        for (int i = 0; i < 500000; i++)
            ;
    }
}
