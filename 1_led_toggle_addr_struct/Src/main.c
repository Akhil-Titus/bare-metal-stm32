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

// Enable clock on port C gpio_en
#define IOPCEN (1U << 4) // 0b 0000 0000 0000 0001 0000  shift value 1 to position 4 ie port C

#define ODR13 (1U << 13)
#define LED_PIN ODR13


#define __IO volatile

typedef struct
{
	volatile uint32_t DUMMY1[1];
	volatile uint32_t CRH;
	volatile uint32_t DUMMY[1];
	volatile uint32_t ODR;
} GPIO_TypeDef;
// CRH ODR

typedef struct
{
	volatile uint32_t DUMMY[6];
	volatile uint32_t APB2ENR;
} RCC_TypeDef;
// RCC_APB2ENR

#define RCC 	((RCC_TypeDef *)RCC_BASE)
#define GPIOC 	((GPIO_TypeDef *)GPIOC_BASE)

int main(void)
{

	// Enable the clock for GPIOC peripheral in the APB2 bus
	RCC->APB2ENR |= IOPCEN;
	// Clear the Bit
	GPIOC->CRH &= ~(15U << 20);
	GPIOC->CRH |= (1U << 21);


	while (1)
	{
		GPIOC->ODR ^= LED_PIN;
		for (int i = 0; i < 500000; i++)
			;
	}
}
