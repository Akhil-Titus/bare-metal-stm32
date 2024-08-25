#include <stdint.h>

#define PERIPH_BASE (0x40000000UL)
#define APB2PERIPH_OFFSET (0x10000UL)
#define APB2PERIPH_BASE (PERIPH_BASE + APB2PERIPH_OFFSET) //  0x4001 0000

#define GPIOC_OFFSET (0x1000UL)						// 0x0000 1000
#define GPIOC_BASE (APB2PERIPH_BASE + GPIOC_OFFSET) // 0x4001 1000

//  RCC resetting clock control 0x4002 1000 --RCC in AHB
#define PERIPH2_BASE (0x40010000UL)
#define AHBPERIPH_OFFSET (0x8000UL)
#define AHBPERIPH_BASE (PERIPH2_BASE + AHBPERIPH_OFFSET) // 0x4001 8000

#define RCC_OFFSET (0x9000UL)				   // RCC_BASE - AHBPERIPH_BASE
#define RCC_BASE (AHBPERIPH_BASE + RCC_OFFSET) // 0x4002 1000

#define APB2EN_R_OFFSET (0x18UL)
#define RCC_APB2ENR (*(volatile unsigned int *)(RCC_BASE + APB2EN_R_OFFSET)) //*** 0x40021018

// Port configuration register high (GPIOx_CRH) (x=A..G)
#define CRH_R_OFFSET (0x04UL)
#define GPIOC_CRH (*(volatile unsigned int *)(GPIOC_BASE + CRH_R_OFFSET)) //*** 0x4001 1004

// Port output data register (GPIOx_ODR) (x=A..G)
#define ODR_R_OFFSET (0x0CUL)
#define GPIOC_ODR (*(volatile unsigned int *)(GPIOC_BASE + ODR_R_OFFSET)) //*** 0x4001100C

// Enable clock on port C gpio_en
#define IOPCEN (1U << 4) // 0b 0000 0000 0000 0001 0000  shift value 1 to position 4 ie port C

#define ODR13 (1U << 13)
#define LED_PIN ODR13

/* set only these bits to zero to clear the bits
 * 23-22 CNF13[1:0]     --> 00  &=~(1U << 23)    &=~(1U << 22)      
 * 21-20 MODE13[1:0]    --> 10     (1U << 21)    &=~(1U << 20)
 */

int main(void)
{

	// Enable the clock for GPIOC peripheral in the APB2 bus
	RCC_APB2ENR |= IOPCEN;
	// Clear the Bit
	/*
	GPIOC_CRH &= ~(1U << 20);
	GPIOC_CRH &= ~(1U << 21);
	GPIOC_CRH &= ~(1U << 22);
	GPIOC_CRH &= ~(1U << 23);
	*/
	GPIOC_CRH &= ~(15U << 20); // binary of 15 is 1111 hence will add to 20 21 22 23
	//  Set as Output
	GPIOC_CRH |= (1U << 21);

	while (1)
	{
		/*
		GPIOC_ODR |= LED_PIN;
		for (int i = 0; i < 500000; i++)
			;
		GPIOC_ODR &= ~LED_PIN;
		for (int i = 0; i < 500000; i++)
			;
		*/
		GPIOC_ODR ^= LED_PIN;
		for (int i = 0; i < 500000; i++)
			;
	}
}
