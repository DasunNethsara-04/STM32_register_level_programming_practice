#include "stm32f411xe.h"
#include "stm32f4xx_hal.h"
#include <stdint.h>

int main(void) {

  HAL_Init();

  // input -> A4
  // output -> B4
  //

  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

  // set the pin mode
  // input
  GPIOA->MODER &= ~GPIO_MODER_MODER4_0;
  GPIOA->MODER &= ~GPIO_MODER_MODER4_1;

  // output
  GPIOB->MODER |= GPIO_MODER_MODER4_0;
  GPIOB->MODER &= ~GPIO_MODER_MODER4_1;

  // set the output type
  GPIOB->OTYPER &= ~GPIO_OTYPER_OT_4;

  // set the output speed
  GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED4;

  // set the pull up, pull down
  GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD4;
  GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD4;

  uint32_t previousButtonState = !!(GPIOA->IDR & GPIO_IDR_ID4);
  uint32_t currentButtonState;

  while (1) {
    currentButtonState = !!(GPIOA->IDR & GPIO_IDR_ID4);

    if (currentButtonState == 1 && previousButtonState == 0) {

      HAL_Delay(50);
      currentButtonState = !!(GPIOA->IDR & GPIO_IDR_ID4);

      if (currentButtonState) {
        // toggle the LED state
        GPIOB->ODR ^= GPIO_ODR_OD4;
      }
    }
    previousButtonState = currentButtonState;
  }
}
