#include <stdint.h>
#include "main.h"

volatile uint32_t counter = 0;

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

void setupInputPin(GPIO_TypeDef *port, uint32_t pin) {
	// set the pin mode as output
	port->MODER &= ~(3UL << (2 * pin)); // clean the bits

	// set the pull-up/ pull-down as NO
	port->PUPDR &= ~(3UL << (2 * pin));
}

// interrupt handler for the timer
void TIM2_IRQHandler() {
	if(TIM2->SR & (1UL << 0)) {
		// clear the update interrupt handler bit (UIF)
		TIM2->SR &= ~(1UL << 0);

		counter++;

		if(counter == 300) {
			// turn off the LED after 3 seconds
			GPIOA->BSRR = (1UL << 19);
			// stop the timer
			TIM2->CR1 &= ~(1UL << 0);
			counter = 0;
		}
	}
}

// interrupt handler for the button
void EXTI9_5_IRQHandler() {
	if(EXTI->PR & (1UL << 5)) {
		// clear the bit
		EXTI->PR = (1UL << 5);

		// turn on the LED
		GPIOA->BSRR = (1UL << 3);

		// start the timer
		TIM2->CR1 |= (1UL << 0);
	}
}

int main(void) {
	// enable the clock for SYSCFG
	RCC->APB2ENR |= (1UL << 14);
	// enable the clock for GPIOA
	RCC->AHB1ENR |= (1UL << 0);
	// enable the clock for TIM2
	RCC->APB1ENR |= (1UL << 0);

	// configure the A3 as output
	setupOutputPins(GPIOA, 3);

	// configure the A5 as input
	setupInputPin(GPIOA, 5);

	// setup the timer (TIM2)
	TIM2->PSC = 16000 - 1;
	TIM2->ARR = 10 - 1;

	// enable the timer interrupt
	TIM2->DIER |= (1UL << 0);

	// setup an interrupt for the button press
	SYSCFG->EXTICR[1] &= ~(0xFUL << 4);

	EXTI->RTSR |= (1UL << 5);

	EXTI->IMR |= (1UL << 5);

	NVIC_EnableIRQ(EXTI9_5_IRQn); // for the button
	NVIC_EnableIRQ(TIM2_IRQn); // for the timer

	while (1) {
		//
	}
}
