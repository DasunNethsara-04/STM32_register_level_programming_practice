#include <stdint.h>
#include "main.h"

volatile uint32_t hours = 0;    // for hours
volatile uint32_t minutes = 0;  // for minutes
volatile uint32_t seconds = 0;  // for seconds

void TIM2_IRQHandler() {
	if (TIM2->SR & (0x1UL << 0x0UL)) {
		//clear the UIF bit
		TIM2->SR &= ~(0x1UL << 0x0UL);

		seconds++;

		if (seconds == 60) {
			// reset the seconds counter to 0
			seconds = 0;
			// increment minutes counter by 1
			minutes++;
		}
		if (minutes == 60) {
			// reset the minutes counter to 0
			minutes = 0;
			// increment hours counter by 1
			hours++;
		}
	}
}

int main(void) {
	// enable clock for the TIM2
	RCC->APB1ENR |= (0x1UL << 0x0UL);

	// configure the TIM2 timer
	TIM2->PSC = 16000 - 1;
	TIM2->ARR = 1000 - 1;

	// enable the timer-interrupt
	TIM2->DIER |= (0x1UL << 0x0UL);

	NVIC_EnableIRQ(TIM2_IRQn);

	// enable the counter
	TIM2->CR1 |= (0x1UL << 0x0UL);

	while (1) {
		//
	}
}
