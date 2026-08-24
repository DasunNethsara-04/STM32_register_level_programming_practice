#include "main.h"
#include "stm32f411xe.h"
#include "stm32f4xx_hal.h"

int main(void) {
  HAL_Init();

  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

  GPIOB->MODER |= GPIO_MODER_MODE4_0;
  GPIOB->MODER &= ~GPIO_MODER_MODE4_1;
  GPIOB->MODER |= GPIO_MODER_MODE5_0;
  GPIOB->MODER &= ~GPIO_MODER_MODE5_1;

  GPIOB->OTYPER &= ~GPIO_OTYPER_OT4;
  GPIOB->OTYPER &= ~GPIO_OTYPER_OT5;

  GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED4;
  GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED5;

  GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD4;
  GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD5;

  // GPIOB->ODR |= GPIO_ODR_OD4;
  // GPIOB->ODR &= ~GPIO_ODR_OD4;

  while (1) {
    // using BSRR - Bit Set / Reset Register
    // use two LEDs

    // turn on the first LED
    GPIOB->BSRR = GPIO_BSRR_BS4;
    HAL_Delay(500);
    // turn off the first LED
    GPIOB->BSRR = GPIO_BSRR_BR4;

    // turn on the second LED
    GPIOB->BSRR = GPIO_BSRR_BS5;
    HAL_Delay(500);
    GPIOB->BSRR = GPIO_BSRR_BR5;
  }
}