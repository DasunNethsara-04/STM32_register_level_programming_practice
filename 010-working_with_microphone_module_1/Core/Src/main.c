#include "stm32f411xe.h"
#include "stm32f4xx_hal.h"
#include <stdbool.h>
#include <stdint.h>

int main(void) {
  HAL_Init();

  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

  // make the A4 as input and B5 as output
  GPIOA->MODER &= ~GPIO_MODER_MODE4;
  GPIOB->MODER |= GPIO_MODER_MODE5_0;
  GPIOB->MODER &= ~GPIO_MODER_MODE5_1;

  // set the output type
  GPIOB->OTYPER &= ~GPIO_OTYPER_OT_5;

  // set the output speed
  GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED5;

  // set the pull up/ pull down
  GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD4;
  GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD5;

  uint8_t previousMicState = !!(GPIOA->IDR & GPIO_IDR_ID4);
  uint8_t currentMicState;

  while (true) {
    currentMicState = !!(GPIOA->IDR & GPIO_IDR_ID4);
    if (currentMicState == 1 && previousMicState == 0) {
      // HAL_Delay(20);
      currentMicState = !!(GPIOA->IDR & GPIO_IDR_ID4);
      if (currentMicState) {
        // toggle the LED state
        GPIOB->ODR ^= GPIO_ODR_OD5;
      }
    }
    previousMicState = currentMicState;
  }
}