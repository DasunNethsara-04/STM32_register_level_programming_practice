#include <stdint.h>
#include "main.h"

void TIM2_IRQHandler() {
	if (TIM2->SR & (1UL << 0)) {
		// clear the SR
		TIM2->SR &= ~(1UL << 0);
		// toggle the LED
		GPIOA->ODR ^= (1UL << 3);
	}
}

void setupOutputPin(GPIO_TypeDef *port, uint8_t pin) {
	// setup pin mode as output
	port->MODER &= ~(3UL << (2 * pin));
	port->MODER |= (1UL << (2 * pin));

	// set the output type as push-pull
	port->OTYPER &= ~(1UL << pin);

	// set the output type as high speed
	port->OSPEEDR |= (3UL << (2 * pin));

	// set the pull up/ pull down as No
	port->PUPDR &= ~(3UL << (2 * pin));
}

int main(void) {
	// enable clocks for GPIOA and TIM2
	// for GPIOA
	RCC->AHB1ENR |= (1UL << 0);
	// for TIM2 timer
	RCC->APB1ENR |= (1UL << 0);

	// setup the output pin (A3)
	setupOutputPin(GPIOA, 3);

	// setup the timer
	// clock = 16MHz = 16,000,000Hz
	TIM2->PSC = 16000 - 1;
	TIM2->ARR = 1000 - 1;

	// now the LED will blink for 500ms times
	// If ARR = 1000 -> blink for 1000ms (1s)
	// If ARR = 500 -> blink for 500ms (0.5s)

	// setup the interrupt for the timer
	// enable interrupt register
	TIM2->DIER |= (1UL << 0);

	// enable the clock
	TIM2->CR1 |= (1UL << 0);

	NVIC_EnableIRQ(TIM2_IRQn);

	while (1) {
		//
	}
}
