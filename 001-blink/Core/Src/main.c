#include "stm32f411xe.h"
#include "stm32f4xx_hal.h"

int main(void) {
  HAL_Init();

  // turn on the GPIOB clock
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

  // mode register
  GPIOC->MODER |= GPIO_MODER_MODER13_0;
  GPIOC->MODER &= ~GPIO_MODER_MODER13_1;

  // type register
  GPIOC->OTYPER &= ~GPIO_OTYPER_OT_13;

  // speed register
  GPIOC->OSPEEDR |= GPIO_OSPEEDR_OSPEED13_0;
  GPIOC->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED13_1;

  // pull up/ pull down register
  // GPIOC->PUPDR |= GPIO_PUPDR_PUPDR4_0;
  GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR13_0;
  GPIOC->PUPDR &= ~GPIO_PUPDR_PUPDR13_1;

  while (1) {
    // turn on the LED
    GPIOC->ODR ^= GPIO_ODR_OD13;
    HAL_Delay(500);
  }
}