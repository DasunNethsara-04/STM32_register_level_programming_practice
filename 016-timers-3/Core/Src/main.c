#include <stdint.h>
#include "main.h"

// blink 3 LEDs (A1, A2, A3) with different delays
// but only using one timer (TIM2)

volatile uint32_t counter1 = 0; // for 250ms counter
volatile uint32_t counter2 = 0; // for 500ms counter
volatile uint32_t counter3 = 0; // for 100ms counter

void setupOutputPins(GPIO_TypeDef *port, uint32_t pin) {
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

void TIM2_IRQHandler() {
	if (TIM2->SR & (1UL << 0)) {
		// clear the update interrupt flag register bit
		TIM2->SR &= ~(1UL << 0);

		counter1++;
		counter2++;
		counter3++;

		if (counter1 == 25) {
			//  toggle the first LED (A1)
			GPIOA->ODR ^= (1UL << 1);
			// reset the counter1
			counter1 = 0;
		}
		if (counter2 == 50) {
			//  toggle the second LED (A2)
			GPIOA->ODR ^= (1UL << 2);
			// reset the counter2
			counter2 = 0;
		}
		if (counter3 == 100) {
			//  toggle the third LED (A3)
			GPIOA->ODR ^= (1UL << 3);
			// reset the counter3
			counter3 = 0;
		}
	}
}

int main(void) {
	// enable clock for GPIOA
	RCC->AHB1ENR |= (1UL << 0);
	// enable clock for the timer (TIM2)
	RCC->APB1ENR |= (1UL << 0);

	// set the A1, A2, A3 pins as outputs
	setupOutputPins(GPIOA, 1);
	setupOutputPins(GPIOA, 2);
	setupOutputPins(GPIOA, 3);

	// setup the timer
	TIM2->PSC = 16000 - 1;
	TIM2->ARR = 10 - 1;

	// enable the Timer interrupt
	TIM2->DIER |= (1UL << 0);

	NVIC_EnableIRQ(TIM2_IRQn);

	// start the counter
	TIM2->CR1 |= (1UL << 0);

	while (1) {

	}
}
