#include "main.h"
#include "stm32f411xe.h"

int main(void) {
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

  // set the pin B4 as output
  GPIOB->MODER |= GPIO_MODER_MODER4_0;
  GPIOB->MODER &= ~GPIO_MODER_MODER4_1;

  // set the pin B5 as input
  GPIOB->MODER &= ~GPIO_MODER_MODER5_0;
  GPIOB->MODER &= ~GPIO_MODER_MODER5_1;

  // set the output type
  GPIOB->OTYPER &= ~GPIO_OTYPER_OT_4;

  // set the output speed
  GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED4_0;
  GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED4_1;

  // set the pull up/ pull down to pin B4 (LED)
  GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD4_0;
  GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD4_1;

  // set the pull up/ pull down to pin B5 (button) because it already pulled
  // down using a external resistor
  GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD5_0;
  GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD5_1;

  while (1) {
    // check the IDR for input
    if (GPIOB->IDR & GPIO_IDR_ID5) {
      // turn on the LED
      GPIOB->ODR |= GPIO_ODR_OD4;
    } else {
      // turn off the LED
      GPIOB->ODR &= ~GPIO_ODR_OD4;
    }
  }
}
