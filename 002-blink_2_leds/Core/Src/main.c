#include "stm32f411xe.h"
#include "stm32f4xx_hal.h"

int main(void) {
  HAL_Init();

  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

  // set the pin mode for pin 3
  GPIOB->MODER |= GPIO_MODER_MODER3_0;
  GPIOB->MODER &= ~GPIO_MODER_MODER3_1;

  // set the pin mode for pin 4
  GPIOB->MODER |= GPIO_MODER_MODER4_0;
  GPIOB->MODER &= ~GPIO_MODER_MODER4_1;

  // set the output type for pin 3 and pin 4
  GPIOB->OTYPER &= ~GPIO_OTYPER_OT_3;
  GPIOB->OTYPER &= ~GPIO_OTYPER_OT_4;

  // set the speed
  GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED3_0;
  GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED3_1;

  GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED4_0;
  GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED4_1;

  // set the pull up/ pull-down
  GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD3_0;
  GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR3_1;

  GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD4_0;
  GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR4_1;

  // turn the LED on pin 3 on
  // GPIOB->ODR |= GPIO_ODR_OD3;

  while (1) {
    GPIOB->ODR |= GPIO_ODR_OD3;
    HAL_Delay(500);
    GPIOB->ODR &= ~GPIO_ODR_OD3;

    GPIOB->ODR |= GPIO_ODR_OD4;
    HAL_Delay(500);
    GPIOB->ODR &= ~GPIO_ODR_OD4;
  }
}