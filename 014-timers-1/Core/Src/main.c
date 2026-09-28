#include <stdint.h>
#include "main.h"

volatile uint16_t timer_value = 0;

int main(void) {
	// enable clock for the timer (TIM2)
	RCC->APB1ENR |= (1UL << 0);

	// set the prescaler
	// TIM2 freq = 16MHz = 16,000,000Hz
	// Prescaler = 16,000
	TIM2->PSC = 16000 - 1;

	// auto reload
	TIM2->ARR = 1000 - 1;

	// start the counter
	TIM2->CR1 |= (1UL << 0);

	while (1) {
		timer_value = TIM2->CNT;
	}
}
