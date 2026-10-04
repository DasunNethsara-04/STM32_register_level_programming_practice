#include <stdint.h>
#include <stddef.h>
#include "main.h"

// Rotate a servo motor

void setupAlternateFunctionPin(GPIO_TypeDef *port, uint16_t pin, uint32_t af_no) {
	// simple validation before processing part
	if (pin > 15 || af_no > 15)
		return;
	// setup pin as alternate function mode
	port->MODER &= ~(0x3UL << (2 * pin));
	port->MODER |= (0x2UL << (2 * pin));

	// set output type as push-pull
	port->OTYPER &= ~(0x1UL << pin);

	// set output speed as high speed
	port->OSPEEDR &= ~(0x3UL << (2 * pin));
	port->OSPEEDR |= (0x3UL << (2 * pin));

	// set the pull up/down as NO
	port->PUPDR &= ~(0x3UL << (2 * pin));

	if (pin <= 7) {
		port->AFR[0] &= ~(0xFUL << (4 * pin));
		port->AFR[0] |= (af_no << (4 * pin));
	} else {
		port->AFR[1] &= ~(0xFUL << (4 * (pin - 8)));
		port->AFR[1] |= (af_no << (4 * (pin - 8)));
	}
}

const uint16_t CCR1_Values[] = { 500, 1000, 1500, 2000 };

int main(void) {
	HAL_Init();
	// enable clock for GPIOA
	RCC->AHB1ENR |= (0x1UL << 0x0UL);

	// enable clock for TIM2
	RCC->APB1ENR |= (0x1UL << 0x0UL);

	setupAlternateFunctionPin(GPIOA, 5, 1);

	// timer configuration
	TIM2->PSC = 16 - 1;
	TIM2->ARR = 20000 - 1;

	// enable PWM mode 1 on capture and compare mode register 1
	TIM2->CCMR1 &= ~(0x7UL << 0x4UL);
	TIM2->CCMR1 |= (0x6UL << 0x4UL);

	TIM2->CCR1 = 500;

	// enable the capture and compare 1 output register
	TIM2->CCER |= (0x1UL << 0x0UL);

	// enable the counter
	TIM2->CR1 |= (0x1UL << 0x0UL);

	while (1) {
		for (size_t i = 0; i < (sizeof(CCR1_Values) / sizeof(CCR1_Values[0]));
				i++) {
			TIM2->CCR1 = CCR1_Values[i];
			HAL_Delay(500);
		}
	}
}
