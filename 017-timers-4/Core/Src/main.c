#include <stdint.h>
#include "main.h"

// Blink 4 LEDs with different delays
// but only using one timer (TIM2)

volatile uint32_t counter1 = 0;  // for 250ms counter
volatile uint32_t counter2 = 0;  // for 500ms counter
volatile uint32_t counter3 = 0;  // for 750ms counter
volatile uint32_t counter4 = 0;  // for 1000ms counter

void setupPinsForOutput(GPIO_TypeDef *port, uint32_t pin) {
	// set the pin mode as output
	port->MODER &= ~(3UL << (2 * pin)); // clean the bits
	port->MODER |= (1UL << (2 * pin)); // set the bit

	// set the output type as push-pull
	port->OTYPER &= ~(1UL << pin);

	// set the output speed as high speed
	port->OSPEEDR |= (3UL << (2 * pin));

	// set the pull-up/ pull-down as NO
	port->PUPDR &= ~(3UL << (2 * pin));
}

// interrupt handler
void TIM2_IRQHandler() {
	if (TIM2->SR & (1UL << 0)) {
		// clear the update interrupt flag (UIF)
		TIM2->SR &= ~(1UL << 0);

		counter1++;
		counter2++;
		counter3++;
		counter4++;

		// for the 250ms timer
		if (counter1 == 25) {
			// toggle the LDE 1's state
			GPIOA->ODR ^= (1UL << 1);
			// reset the counter 1
			counter1 = 0;
		}

		// for the 500ms timer
		if (counter2 == 50) {
			// toggle the LDE 2's state
			GPIOA->ODR ^= (1UL << 2);
			// reset the counter 2
			counter2 = 0;
		}
		// for the 750ms timer
		if (counter3 == 75) {
			// toggle the LDE 1's state
			GPIOA->ODR ^= (1UL << 3);
			// reset the counter 3
			counter3 = 0;
		}

		// for the 1000ms timer
		if (counter4 == 100) {
			// toggle the LDE 1's state
			GPIOA->ODR ^= (1UL << 4);
			// reset the counter 4
			counter4 = 0;
		}
	}
}

int main(void) {

	// enable clock for GPIOA
	RCC->AHB1ENR |= (1UL << 0);
	// enable clock for TIM2
	RCC->APB1ENR |= (1UL << 0);

	// configure output pins A1, A2, A3 and A4 as output pins
	setupPinsForOutput(GPIOA, 1);
	setupPinsForOutput(GPIOA, 2);
	setupPinsForOutput(GPIOA, 3);
	setupPinsForOutput(GPIOA, 4);

	// setup timer (TIM2)
	TIM2->PSC = 16000 - 1;
	TIM2->ARR = 10 - 1;

	// enable timer interrupt
	TIM2->DIER |= (1UL << 0);

	NVIC_EnableIRQ(TIM2_IRQn);

	// start the counter
	TIM2->CR1 |= (1UL << 0);

	while (1) {
		//
	}
}
