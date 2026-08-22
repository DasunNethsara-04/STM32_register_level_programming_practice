#include "stm32f411xe.h"
#include "stm32f4xx_hal.h"

int main(void) {
  HAL_Init();

  // turn on the GPIOB clock
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

  // mode register
  GPIOB->MODER |= GPIO_MODER_MODER4_0;
  GPIOB->MODER &= ~GPIO_MODER_MODER4_1;

  // type register
  GPIOB->OTYPER &= ~GPIO_OTYPER_OT_4;

  // speed register
  GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED4_0;
  GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED4_1;

  // pull up/ pull down register
  // GPIOB->PUPDR |= GPIO_PUPDR_PUPDR4_0;
  GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR4_0;
  GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR4_1;

  while (1) {
    // turn on the LED
    GPIOB->ODR ^= GPIO_ODR_OD4;
    HAL_Delay(500);
  }
}